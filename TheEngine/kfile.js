const path = require('path');
const fs = require('fs');
let project = new Project('engine');
 
project.addProvider = function(proj, isRoot=false){
    const sdl2 = true;//process.argv.indexOf("--sdl2") >= 0;
    if(sdl2){
        
        const progx86 = process.env["ProgramFiles(x86)"];
        if(!isRoot){
            proj.addDefine("USE_SDL");
            proj.addIncludeDir(path.resolve("./sdl/include"));
            proj.addIncludeDir(path.resolve(progx86+"/Visual Leak Detector/include"));
            //proj.addIncludeDir(path.resolve("../sdl_image/include"));
        }
        proj.addLib("../sdl/lib/SDL2");
        proj.addLib("../sdl/lib/SDL2main");
        proj.addLib("../sdl/lib/SDL2_image"); //---Image
        proj.addLib("../sdl/lib/SDL2_ttf"); //---Font
        proj.addLib("../sdl/lib/SDL2_mixer"); //---Audio
        proj.addLib(path.resolve(progx86+"/Visual Leak Detector/lib/Win64/vld")); 
        fs.copyFileSync("./sdl/lib/SDL2.dll", "./Deployment/SDL2.dll");
        fs.copyFileSync("./sdl/lib/SDL2_image.dll", "./Deployment/SDL2_image.dll"); //---Image
        fs.copyFileSync("./sdl/lib/SDL2_ttf.dll", "./Deployment/SDL2_ttf.dll"); //---Font
        fs.copyFileSync("./sdl/lib/SDL2_mixer.dll", "./Deployment/SDL2_mixer.dll"); //---Font
    }
};
project.kore = false;


project.addDefine("KINC_STATIC_COMPILE");
project.isStaticLib = true;

project.addIncludeDir(path.resolve("./TheEngine/includes"));
project.addFiles('sources/**','includes/**');

project.addProvider(project,false);

resolve(project);