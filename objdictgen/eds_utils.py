#!/usr/bin/env python
# -*- coding: utf-8 -*-

#This file is part of CanFestival, a library implementing CanOpen Stack. 
#
#Copyright (C): Edouard TISSERANT, Francis DUPIN and Laurent BESSARD
#
#See COPYING file for copyrights details.
#
#This library is free software; you can redistribute it and/or
#modify it under the terms of the GNU Lesser General Public
#License as published by the Free Software Foundation; either
#version 2.1 of the License, or (at your option) any later version.
#
#This library is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#Lesser General Public License for more details.
#
#You should have received a copy of the GNU Lesser General Public
#License along with this library; if not, write to the Free Software
#Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


import node
from sets import *
from types import *
from time import *
import os,re

# Regular expression for finding index section names
index_model = re.compile('([0-9a-fA-F]{1,4})')
# Regular expression for finding subindex section names
subindex_model = re.compile('([0-9a-fA-F]{1,4})sub([0-9a-fA-F]{1,2})')

# Dictionary for quickly translate boolean into integer value
BOOL_TRANSLATE = {True : "1", False : "0"}

# Function for verifying data values
is_integer = lambda x: type(x) == IntType
is_string = lambda x: type(x) == StringType

# Define checking of value for each attribute
ENTRY_ATTRIBUTES = {"SUBNUMBER" : is_integer, "PARAMETERNAME" : is_string, 
                    "OBJECTTYPE" : lambda x: x in (7, 8, 9), "DATATYPE" : is_integer, 
                    "LOWLIMIT" : is_integer, "HIGHLIMIT" : is_integer,
                    "ACCESSTYPE" : lambda x: x in ["ro","wo", "rw", "rwr", "rww", "const"],
                    "DEFAULTVALUE" : lambda x: True, "PDOMAPPING" : lambda x: x in (0, 1),
                    "OBJFLAGS" : is_integer}

# Define entry parameters by entry ObjectType number
ENTRY_TYPES = {7 : {"name" : " VAR",
                    "require" : ["PARAMETERNAME", "OBJECTTYPE", "DATATYPE", "ACCESSTYPE", "PDOMAPPING"],
                    "optional" : ["LOWLIMIT", "HIGHLIMIT", "DEFAULTVALUE", "OBJFLAGS"]},
               8 : {"name" : "n ARRAY",
                    "require" : ["SUBNUMBER", "PARAMETERNAME", "OBJECTTYPE"],
                    "optional" : ["OBJFLAGS"]},
               9 : {"name" : " RECORD",
                    "require" : ["SUBNUMBER", "PARAMETERNAME", "OBJECTTYPE"],
                    "optional" : ["OBJFLAGS"]}}


# Function that search into Node Mappings the informations about an index or a subindex
# and return the default value
def GetDefaultValue(index, subIndex = None):
    infos = Manager.GetEntryInfos(index, Node)
    if infos["struct"] & node.OD_MultipleSubindexes:
        # First case entry is a record
        if infos["struct"] & node.OD_IdenticalSubindexes:
            subentry_infos = Manager.GetSubentryInfos(index, 1, Node)
        # Second case entry is an array
        else:
            subentry_infos = Manager.GetSubentryInfos(index, subIndex, Node)
        # If a default value is defined for this subindex, returns it
        if "default" in subentry_infos:
            return subentry_infos["default"]
        # If not, returns the default value for the subindex type
        else:
            return Manager.GetTypeDefaultValue(subentry_infos["type"], Node)
    # Third case entry is a var
    else:
        subentry_infos = Manager.GetSubentryInfos(index, 0, Node)
        # If a default value is defined for this subindex, returns it
        if "default" in subentry_infos:
            return subentry_infos["default"]
        # If not, returns the default value for the subindex type
        else:
            return Manager.GetTypeDefaultValue(subentry_infos["type"], Node)
    return None


#-------------------------------------------------------------------------------
#                               Parse file
#-------------------------------------------------------------------------------


# List of section names that are not index and subindex and that we can meet in
# an EDS file
SECTION_KEYNAMES = ["FILEINFO", "DEVICEINFO", "DUMMYUSAGE", "COMMENTS", 
                    "MANDATORYOBJECTS", "OPTIONALOBJECTS", "MANUFACTUREROBJECTS"]


# Function that parse an EDS file and returns a dictionary of the informations
def ParseFile(filepath):
    eds_dict = {}
    # Read file text
    eds_file = open(filepath,'r').read()
    sections = [(blocktuple[0],                # EntryName : Assignements dict
                 blocktuple[-1].splitlines())  # all the lines
                 for blocktuple in [           # Split the eds files into
                 block.split("]")              # (EntryName,Assignements) tuple
                 for block in                  # for each blocks staring with '['
                 eds_file.split("[")]
                 if blocktuple[0].isalnum()]   # if EntryName exists
    
    # Parse assignments for each section
    for section_name, assignments in sections:
        # Reset values of entry
        values = {}
        
        # Search if the section name match an index or subindex expression
        index_result = index_model.match(section_name)
        subindex_result = subindex_model.match(section_name)
        
        # Compilation of the EDS information dictionary
        
        is_entry = False
        # First case, section name is in SECTION_KEYNAMES 
        if section_name.upper() in SECTION_KEYNAMES:
            # Verify that entry is not already defined
            if section_name.upper() not in eds_dict:
                eds_dict[section_name.upper()] = values
            else:
                raise SyntaxError, "\"[%s]\" section is defined two times"%section_name
        # Second case, section name is a subindex name 
        elif subindex_result:
            # Extract index and subindex number
            index, subindex = [int(value, 16) for value in subindex_result.groups()]
            # If index hasn't been referenced before, we add an entry into the dictionary
            # that will be updated later
            if index not in eds_dict:
                eds_dict[index] = {"subindexes" : {}}
            if subindex not in eds_dict[index]["subindexes"]:
                eds_dict[index]["subindexes"][subindex] = values
            else:
                raise SyntaxError, "\"[%s]\" section is defined two times"%section_name
            is_entry = True
        # Third case, section name is an index name 
        elif index_result:
            # Extract index number
            index = int(index_result.groups()[0], 16)
            # If index hasn't been referenced before, we add an entry into the dictionary
            if index not in eds_dict:
                eds_dict[index] = values
                eds_dict[index]["subindexes"] = {}
            elif eds_dict[index].keys() == ["subindexes"]:
                values["subindexes"] = eds_dict[index]["subindexes"]
                eds_dict[index] = values
            else:
                raise SyntaxError, "\"[%s]\" section is defined two times"%section_name
            is_entry = True
        # In any other case, there is a syntax problem into EDS file
        else:
            raise SyntaxError, "Section \"[%s]\" is unrecognized"%section_name
        
        for assignment in assignments:
            # Escape any comment
            if assignment.startswith(";"):
                pass
            # Verify that line is a valid assignment
            elif assignment.find('=') > 0:
                # Split assignment into the two values keyname and value
                try:
                    keyname, value = assignment.split("=")
                except:
                    raise SyntaxError, "\"%s\" is not a valid EDS line"%assignment.strip()
                # keyname must be immediately followed by the "=" sign, so we
                # verify that there is no whitespace into keyname
                if keyname.isalnum():
                    # value can be preceded and followed by whitespaces, so we escape them
                    value = value.strip()
                    # First case, value starts with "$NODEID", then it's a formula
                    if value.startswith("$NODEID"):
                        try:
                            computed_value = int(value.replace("$NODEID+", ""), 16)
                        except:
                            raise SyntaxError, "\"%s\" is not a valid formula for attribute \"%s\" of section \"[%s]\""%(value, keyname, section_name)
                    # Second case, value starts with "0x", then it's an hexadecimal value
                    elif value.startswith("0x"):
                        try:
                            computed_value = int(value, 16)
                        except:
                            raise SyntaxError, "\"%s\" is not a valid value for attribute \"%s\" of section \"[%s]\""%(value, keyname, section_name)
                    elif value.isdigit():
                        # Third case, value is a number and starts with "0", then it's an octal value
                        if value.startswith("0"):
                            computed_value = int(value, 8)
                        # Forth case, value is a number and don't start with "0", then it's a decimal value
                        else:
                            computed_value = int(value)
                    # In any other case, we keep string value
                    else:
                        computed_value = value
                    
                    # Add value to values dictionary
                    if computed_value != "":
                        # If entry is an index or a subindex
                        if is_entry:
                            # Verify that keyname is a possible attribute
                            if keyname.upper() not in ENTRY_ATTRIBUTES:
                                raise SyntaxError, "Keyname \"%s\" not recognised for section \"[%s]\""%(keyname, section_name)
                            # Verify that value is valid
                            elif not ENTRY_ATTRIBUTES[keyname.upper()](computed_value):
                                raise SyntaxError, "Invalid value \"%s\" for keyname \"%s\" of section \"[%s]\""%(value, keyname, section_name)
                            else:
                                values[keyname.upper()] = computed_value
                        else:
                            values[keyname.upper()] = computed_value
            # All lines that are not empty and are neither a comment neither not a valid assignment
            elif assignment.strip() != "":
                raise SyntaxError, "\"%s\" is not a valid EDS line"%assignment.strip()
        
        # If entry is an index or a subindex
        if is_entry:
            # Verify that entry has an ObjectType
            if "OBJECTTYPE" in values.keys():
                # Extract entry ObjectType
                objecttype = values["OBJECTTYPE"]
                # Extract parameters defined
                keys = Set(values.keys())
                keys.discard("subindexes")
                # Extract possible parameters and parameters required
                possible = Set(ENTRY_TYPES[objecttype]["require"] + ENTRY_TYPES[objecttype]["optional"])
                required = Set(ENTRY_TYPES[objecttype]["require"])
                # Verify that parameters defined contains all the parameters required
                if not keys.issuperset(required):
                    missing = required.difference(keys)._data.keys()
                    if len(missing) > 1:
                        attributes = "Attributes %s are"%", ".join(["\"%s\""%attribute for attribute in missing])
                    else:
                        attributes = "Attribute \"%s\" is"%missing[0]
                    raise SyntaxError, "Error on section \"[%s]\":\n%s required for a%s entry"%(section_name, attributes, ENTRY_TYPES[objecttype]["name"])
                # Verify that parameters defined are all in the possible parameters
                if not keys.issubset(possible):
                    unsupported = keys.difference(possible)._data.keys()
                    if len(unsupported) > 1:
                        attributes = "Attributes %s are"%", ".join(["\"%s\""%attribute for attribute in unsupported])
                    else:
                        attributes = "Attribute \"%s\" is"%unsupported[0]
                    raise SyntaxError, "Error on section \"[%s]\":\n%s unsupported for a%s entry"%(section_name, attributes, ENTRY_TYPES[objecttype]["name"])
            else:
                raise SyntaxError, "Error on section \"[%s]\":\nAttribute OBJECTTYPE is required"%section_name
        
    return eds_dict


# Function that write an EDS file after generate it's content
def WriteFile(filepath, content):
    # Open file in write mode
    cfile = open(filepath,"w")
    # Write content
    cfile.write(content)
    # Close file
    cfile.close()


# Function that generate the EDS file content for the current node in the manager
def GenerateFileContent(filepath):
    # Dictionary of each index contents
    indexContents = {}
    
    # Extract local time
    current_time = localtime()
    # Extract node informations
    nodename, nodeid, nodetype, description = Manager.GetCurrentNodeInfos()
    
    # Compiling lists of indexes defined
    entries = [idx for name, idx in Manager.GetCurrentValidIndexes(0, 0xFFFF)]
    
    # Generate FileInfo section
    fileContent = "[FileInfo]\n"
    fileContent += "CreatedBy=CANFestival\n"
    fileContent += "Description=%s\n"%description
    fileContent += "CreationTime=%s"%strftime("%I:%M", current_time)
    # %p option of strftime seems not working, then generate AM/PM by hands
    if strftime("%I", current_time) == strftime("%H", current_time):
        fileContent += "AM\n"
    else:
        fileContent += "PM\n"
    fileContent += "CreationDate=%s\n"%strftime("%m-%d-%Y", current_time)
    fileContent += "FileName=%s\n"%os.path.split(filepath)[-1]
    fileContent += "FileVersion=1\n"
    fileContent += "FileRevision=1\n"
    fileContent += "EDSVersion=3.0\n"
    
    # Generate DeviceInfo section
    fileContent += "\n[DeviceInfo]\n"
    fileContent += "VendorName=CANFestival\n"
    # Use information typed by user in Identity entry
    fileContent += "VendorNumber=0x%8.8X\n"%Manager.GetCurrentEntry(0x1018, 1)
    fileContent += "ProductName=%s\n"%nodename
    fileContent += "ProductNumber=0x%8.8X\n"%Manager.GetCurrentEntry(0x1018, 2)
    fileContent += "RevisionNumber=0x%8.8X\n"%Manager.GetCurrentEntry(0x1018, 3)
    # CANFestival support all baudrates as soon as driver choosen support them
    fileContent += "BaudRate_10=1\n"
    fileContent += "BaudRate_20=1\n"
    fileContent += "BaudRate_50=1\n"
    fileContent += "BaudRate_125=1\n"
    fileContent += "BaudRate_250=1\n"
    fileContent += "BaudRate_500=1\n"
    fileContent += "BaudRate_800=1\n"
    fileContent += "BaudRate_1000=1\n"
    # Select BootUp type from the informations given by user
    fileContent += "SimpleBootUpMaster=%s\n"%BOOL_TRANSLATE[nodetype == "master"]
    fileContent += "SimpleBootUpSlave=%s\n"%BOOL_TRANSLATE[nodetype == "slave"]
    # CANFestival characteristics
    fileContent += "Granularity=8\n"
    fileContent += "DynamicChannelsSupported=0\n"
    fileContent += "CompactPDO=0\n"
    fileContent += "GroupMessaging=0\n"
    # Calculate receive and tranmit PDO numbers with the entry available
    fileContent += "NrOfRXPDO=%d\n"%len([idx for idx in entries if 0x1400 <= idx <= 0x15FF])
    fileContent += "NrOfTXPDO=%d\n"%len([idx for idx in entries if 0x1400 <= idx <= 0x15FF])
    # LSS not supported as soon as DS-302 was not fully implemented
    fileContent += "LSS_Supported=0\n"
    
    # Generate Dummy Usage section
    fileContent += "\n[DummyUsage]\n"
    fileContent += "Dummy0001=0\n"
    fileContent += "Dummy0002=1\n"
    fileContent += "Dummy0003=1\n"
    fileContent += "Dummy0004=1\n"
    fileContent += "Dummy0005=1\n"
    fileContent += "Dummy0006=1\n"
    fileContent += "Dummy0007=1\n"

    # Generate Comments section
    fileContent += "\n[Comments]\n"
    fileContent += "Lines=0\n"
    
    # List of entry by type (Mandatory, Optional or Manufacturer
    mandatories = []
    optionals = []
    manufacturers = []
    
    # For each entry, we generate the entry section or sections if there is subindexes
    for entry in entries:
        # Extract infos and values for the entry
        entry_infos = Manager.GetEntryInfos(entry)
        values = Manager.GetCurrentEntry(entry)
        # Define section name
        text = "\n[%X]\n"%entry
        # If there is only one value, it's a VAR entry
        if type(values) != ListType:
            # Extract the informations of the first subindex
            subentry_infos = Manager.GetSubentryInfos(entry, 0)
            # Generate EDS informations for the entry
            text += "ParameterName=%s\n"%subentry_infos["name"]
            text += "ObjectType=0x7\n"
            text += "DataType=0x%4.4X\n"%subentry_infos["type"]
            text += "AccessType=%s\n"%subentry_infos["access"]
            text += "DefaultValue=%s\n"%values
            text += "PDOMapping=%s\n"%BOOL_TRANSLATE[subentry_infos["pdo"]]
        else:
            # Generate EDS informations for the entry
            text += "ParameterName=%s\n"%entry_infos["name"]
            if entry_infos["struct"] & node.OD_IdenticalSubindexes:
                text += "ObjectType=0x9\n"
            else:
                text += "ObjectType=0x8\n"
            
            # Generate EDS informations for subindexes of the entry in a separate text
            subtext = ""
            # Reset number of subindex defined 
            nb_subentry = 0
            for subentry, value in enumerate(values):
                # Extract the informations of each subindex
                subentry_infos = Manager.GetSubentryInfos(entry, subentry)
                # If entry is not for the compatibility, generate informations for subindex
                if subentry_infos["name"] != "Compatibility Entry":
                    subtext += "\n[%Xsub%X]\n"%(entry, subentry)
                    subtext += "ParameterName=%s\n"%subentry_infos["name"]
                    subtext += "ObjectType=0x7\n"
                    subtext += "DataType=0x%4.4X\n"%subentry_infos["type"]
                    subtext += "AccessType=%s\n"%subentry_infos["access"]
                    subtext += "DefaultValue=%s\n"%value
                    subtext += "PDOMapping=%s\n"%BOOL_TRANSLATE[subentry_infos["pdo"]]
                    # Increment number of subindex defined 
                    nb_subentry += 1
            # Write number of subindex defined for the entry
            text += "SubNumber=%d\n"%nb_subentry
            # Write subindex definitions
            text += subtext
        
        # Then we add the entry in the right list
        
        # First case, entry is between 0x2000 and 0x5FFF, then it's a manufacturer entry
        if 0x2000 <= entry <= 0x5FFF:
            manufacturers.append(entry)
        # Second case, entry is required, then it's a mandatory entry
        elif entry_infos["need"]:
            mandatories.append(entry)
        # In any other case, it's an optional entry
        else:
            optionals.append(entry)
        # Save text of the entry in the dictiionary of contents
        indexContents[entry] = text
    
    # Before generate File Content we sort the entry list
    manufacturers.sort()
    mandatories.sort()
    optionals.sort()
    
    # Generate Definition of mandatory objects
    fileContent += "\n[MandatoryObjects]\n"
    fileContent += "SupportedObjects=%d\n"%len(mandatories)
    for idx, entry in enumerate(mandatories):
        fileContent += "%d=0x%4.4X\n"%(idx, entry)
    # Write mandatory entries
    for entry in mandatories:
        fileContent += indexContents[entry]
    
    # Generate Definition of optional objects
    fileContent += "\n[OptionalObjects]\n"
    fileContent += "SupportedObjects=%d\n"%len(optionals)
    for idx, entry in enumerate(optionals):
        fileContent += "%d=0x%4.4X\n"%(idx, entry)
    # Write optional entries
    for entry in optionals:
        fileContent += indexContents[entry]

    # Generate Definition of manufacturer objects
    fileContent += "\n[ManufacturerObjects]\n"
    fileContent += "SupportedObjects=%d\n"%len(manufacturers)
    for idx, entry in enumerate(manufacturers):
        fileContent += "%d=0x%4.4X\n"%(idx, entry)
    # Write manufacturer entries
    for entry in manufacturers:
        fileContent += indexContents[entry]
    
    # Return File Content
    return fileContent


# Function that generates EDS file from current node edited
def GenerateEDSFile(filepath, manager):
    global Manager
    Manager = manager
    try:
        # Generate file content
        content = GenerateFileContent(filepath)
        # Write file
        WriteFile(filepath, content)
        return None
    except ValueError, message:
        return "Unable to generate EDS file\n%s"%message
    

# Function that generates Node from an EDS file
def GenerateNode(filepath, manager, cwd):
    global Node
    global Manager
    Manager = manager
    # Create a new node
    Node = node.Node()
    try:
        # Parse file and extract dictionary of EDS entry
        eds_dict = ParseFile(filepath)
        # Extract Profile Number from Device Type entry
        ProfileNb = eds_dict[0x1000]["DEFAULTVALUE"] & 0x0000ffff
        # If profile is not DS-301 or DS-302
        if ProfileNb not in [301, 302]:
            # Compile Profile name and path to .prf file
            ProfileName = "DS-%d"%ProfileNb
            ProfilePath = os.path.join(cwd, "config/%s.prf"%ProfileName)
            # Verify that profile is available
            if os.path.isfile(ProfilePath):
                try:
                    # Load Profile
                    execfile(ProfilePath)
                    Node.SetProfileName(ProfileName)
                    Node.SetProfile(Mapping)
                    Node.SetSpecificMenu(AddMenuEntries)
                except:
                    pass
        # Read all entries in the EDS dictionary 
        for entry, values in eds_dict.items():
            # All sections with a name in keynames are escaped
            if entry in SECTION_KEYNAMES:
                pass
            else:
                # Extract informations for the entry
                entry_infos = Manager.GetEntryInfos(entry, Node)
                
                # If no informations are available, then we write them
                if not entry_infos:
                    # First case, entry is a VAR
                    if values["OBJECTTYPE"] == 7:
                        # Add mapping for entry
                        Node.AddMappingEntry(entry, name = values["PARAMETERNAME"], struct = 1)
                        # Add mapping for first subindex
                        Node.AddMappingEntry(entry, 0, values = {"name" : values["PARAMETERNAME"], 
                                                                 "type" : values["DATATYPE"], 
                                                                 "access" : values["ACCESSTYPE"], 
                                                                 "pdo" : values["PDOMAPPING"] == 1})
                    # Second case, entry is an ARRAY
                    elif values["OBJECTTYPE"] == 8:
                        # Extract maximum subindex number defined
                        try:
                            max_subindex = values["subindexes"][0]["DEFAULTVALUE"]
                        except:
                            raise SyntaxError, "Error on entry 0x%4.4X:\nSubindex 0 must be defined for an ARRAY entry"%entry
                        # Add mapping for entry
                        Node.AddMappingEntry(entry, name = values["PARAMETERNAME"], struct = 3)
                        # Add mapping for first subindex
                        Node.AddMappingEntry(entry, 0, values = {"name" : "Number of Entries", "type" : 0x05, "access" : "ro", "pdo" : False})
                        # Add mapping for other subindexes
                        for subindex in xrange(1, int(max_subindex) + 1):
                            # if subindex is defined
                            if subindex in values["subindexes"]:
                                Node.AddMappingEntry(entry, subindex, values = {"name" : values["subindexes"][subindex]["PARAMETERNAME"], 
                                                                                "type" : values["subindexes"][subindex]["DATATYPE"], 
                                                                                "access" : values["subindexes"][subindex]["ACCESSTYPE"], 
                                                                                "pdo" : values["subindexes"][subindex]["PDOMAPPING"] == 1})
                            # if not, we add a mapping for compatibility 
                            else:
                                Node.AddMappingEntry(entry, subindex, values = {"name" : "Compatibility Entry", "type" : 0x05, "access" : "rw", "pdo" : False})
                    # Third case, entry is an RECORD
                    elif values["OBJECTTYPE"] == 9:
                        # Verify that the first subindex is defined
                        if 0 not in values["subindexes"]:
                            raise SyntaxError, "Error on entry 0x%4.4X:\nSubindex 0 must be defined for a RECORD entry"%entry
                        # Add mapping for entry
                        Node.AddMappingEntry(entry, name = values["PARAMETERNAME"], struct = 7)
                        # Add mapping for first subindex
                        Node.AddMappingEntry(entry, 0, values = {"name" : "Number of Entries", "type" : 0x05, "access" : "ro", "pdo" : False})
                        # Verify that second subindex is defined
                        if 1 in values:
                            Node.AddMappingEntry(entry, 1, values = {"name" : values["PARAMETERNAME"] + " %d[(sub)]", 
                                                                     "type" : values["subindexes"][1]["DATATYPE"], 
                                                                     "access" : values["subindexes"][1]["ACCESSTYPE"], 
                                                                     "pdo" : values["subindexes"][1]["PDOMAPPING"] == 1})
                        else:
                            raise SyntaxError, "Error on entry 0x%4.4X:\nA RECORD entry must have at least 2 subindexes"%entry
                
                # Define entry for the new node
                
                # First case, entry is a VAR
                if values["OBJECTTYPE"] == 7:
                    # Take default value if it is defined
                    if "DEFAULTVALUE" in values:
                        value = values["DEFAULTVALUE"]
                    # Find default value for value type of the entry
                    else:
                        value = GetDefaultValue(entry)
                    Node.AddEntry(entry, 0, value)
                # Second case, entry is an ARRAY or a RECORD
                elif values["OBJECTTYPE"] in (8, 9):
                    # Verify that "Subnumber" attribute is defined and has a valid value
                    if "SUBNUMBER" in values and values["SUBNUMBER"] > 0:
                        # Extract maximum subindex number defined
                        try:
                            max_subindex = values["subindexes"][0]["DEFAULTVALUE"]
                        except:
                            raise SyntaxError, "Error on entry 0x%4.4X:\nSubindex 0 must be defined for an ARRAY or a RECORD entry"%entry
                        # Define value for all subindexes except the first 
                        for subindex in xrange(1, int(max_subindex) + 1):
                            # Take default value if it is defined and entry is defined
                            if subindex in values["subindexes"] and "DEFAULTVALUE" in values["subindexes"][subindex]:
                                value = values["subindexes"][subindex]["DEFAULTVALUE"]
                            # Find default value for value type of the subindex
                            else:
                                value = GetDefaultValue(entry, subindex)
                            Node.AddEntry(entry, subindex, value)
                    else:
                        raise SyntaxError, "Array or Record entry 0x%4.4X must have a \"SubNumber\" attribute"%entry
        return Node
    except SyntaxError, message:
        return "Unable to import EDS File\n%s"%message

#-------------------------------------------------------------------------------
#                             Main Function
#-------------------------------------------------------------------------------

if __name__ == '__main__':
    print ParseFile("examples/PEAK MicroMod.eds")

