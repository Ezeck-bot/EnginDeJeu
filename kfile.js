//on va creer un projet

let project = new Project("BattleCity");

project.cppStd = 'c++11';

await project.addProject("./TheEngine");

project.addFile("BattleCity/sources/**");
project.addIncludeDir("BattleCity/includes/**");
project.addFile("BattleCity/includes/**");

project.setDebugDir("Deployment");

project.flatten();

resolve(project);