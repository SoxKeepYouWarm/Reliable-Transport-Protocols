##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=cse489_pa2
ConfigurationName      :=Debug
WorkspacePath          := "/home/david/Documents/cse489/cse489_pa2"
ProjectPath            := "/home/david/Documents/cse489/cse489_pa2"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=David Towson
Date                   :=24/03/16
CodeLitePath           :="/home/david/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="cse489_pa2.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch). $(LibraryPathSwitch)Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -Wall $(Preprocessors)
CFLAGS   :=   $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_abt.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_gbn.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_sr.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_simulator.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_abt.cpp$(ObjectSuffix): davidtow/src/abt.cpp $(IntermediateDirectory)/src_abt.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/david/Documents/cse489/cse489_pa2/davidtow/src/abt.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_abt.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_abt.cpp$(DependSuffix): davidtow/src/abt.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_abt.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_abt.cpp$(DependSuffix) -MM "davidtow/src/abt.cpp"

$(IntermediateDirectory)/src_abt.cpp$(PreprocessSuffix): davidtow/src/abt.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_abt.cpp$(PreprocessSuffix) "davidtow/src/abt.cpp"

$(IntermediateDirectory)/src_gbn.cpp$(ObjectSuffix): davidtow/src/gbn.cpp $(IntermediateDirectory)/src_gbn.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/david/Documents/cse489/cse489_pa2/davidtow/src/gbn.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_gbn.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_gbn.cpp$(DependSuffix): davidtow/src/gbn.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_gbn.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_gbn.cpp$(DependSuffix) -MM "davidtow/src/gbn.cpp"

$(IntermediateDirectory)/src_gbn.cpp$(PreprocessSuffix): davidtow/src/gbn.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_gbn.cpp$(PreprocessSuffix) "davidtow/src/gbn.cpp"

$(IntermediateDirectory)/src_sr.cpp$(ObjectSuffix): davidtow/src/sr.cpp $(IntermediateDirectory)/src_sr.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/david/Documents/cse489/cse489_pa2/davidtow/src/sr.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_sr.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_sr.cpp$(DependSuffix): davidtow/src/sr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_sr.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_sr.cpp$(DependSuffix) -MM "davidtow/src/sr.cpp"

$(IntermediateDirectory)/src_sr.cpp$(PreprocessSuffix): davidtow/src/sr.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_sr.cpp$(PreprocessSuffix) "davidtow/src/sr.cpp"

$(IntermediateDirectory)/src_simulator.cpp$(ObjectSuffix): davidtow/src/simulator.cpp $(IntermediateDirectory)/src_simulator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/david/Documents/cse489/cse489_pa2/davidtow/src/simulator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_simulator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_simulator.cpp$(DependSuffix): davidtow/src/simulator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_simulator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_simulator.cpp$(DependSuffix) -MM "davidtow/src/simulator.cpp"

$(IntermediateDirectory)/src_simulator.cpp$(PreprocessSuffix): davidtow/src/simulator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_simulator.cpp$(PreprocessSuffix) "davidtow/src/simulator.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/

