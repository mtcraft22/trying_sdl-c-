import json
import sys
import os

output = []

if (len(sys.argv[1])>=2):
    dir_prex=""

    dir_prex="/".join(sys.argv[0].split("/")[:-1])
    print(f"[LOG] make output directori: {dir_prex}/makefile")
    with open(sys.argv[1],"r") as data:
        nolose = json.loads(data.read())
    print(f"[LOG]: Detecting objects in: {os.curdir}")
    output.append("objects = $(shell ls ./*.o)\n")
    print(f"[LOG]: Creating make var for the object files")

    include = nolose["directorio_de_cabeceras"]
    print(f"[LOG]: Parsing include path {include}")
    include_parsed  = ""
    
    for i in include.split(" "):
        i = "-I"+i
        include_parsed += i
        include_parsed +=" "
    output.append(f"Include = {include_parsed}\n")
    print(f"[LOG]: Creating make var for the include path: {include_parsed}")
    libs = nolose["librerias"]
    libs_parsed  = ""
    
    for i in libs.split(" "):
        i = "-l"+i
        libs_parsed += i
        libs_parsed +=" "
    output.append(f"lib = {libs_parsed}\n")
    print(f"[LOG]: Creating make var for libs: {libs_parsed}")

    all_rule_dependecies=""
    for i in os.listdir(nolose["fuentes"]):
        output.append(f"{i.split('.')[0]}.o:{nolose['fuentes']}/{i}\n")
        output.append(f"\t{nolose['compilador']} -c {nolose['fuentes']}/{i} $(Include)\n")
        print(f"[LOG]: Added rule for make object file {i.split('.')[0]}.o for file {nolose['fuentes']}/{i} ")
        all_rule_dependecies += f"{i.split('.')[0]}.o "

    output.append(f"all:{all_rule_dependecies}\n")
    output.append(f"\t{nolose['compilador']} -o {nolose['directorio_del_ejecutable']}/{nolose['nombre']} $(objects) $(lib)\n")
    print(f"[LOG]: Added rule for compile project")
    output.append("clear:\n")
    output.append("\trm -r $(objects)\n")
    print(f"[LOG]: created rule for cleaning bin files")
    current = os.curdir
    if (len(dir_prex)>1):
        os.chdir(dir_prex)
        print(f"[LOG] Entry in : {dir_prex}")

    load = 0
    with open("makefile","w") as target:

        for i in output:
            print(f"[LOG] making makefile {load}/{len(output)}")
            target.write(i)
            load += 1
        
    if (len(dir_prex)>1):
        os.chdir(current)
        print(f"[LOG] Entry in : {current}")
    print("[OK]: makefile successfuly builded!!")
