```
clang++ -std=c++2a -c player.cpp -Xclang -emit-module-interface -o player.pcm -fmodules-ts 
clang++ -std=c++2a -stdlib=libc++ -fprebuilt-module-path=. test.cpp player.cpp -fmodules-ts

clang++ -std=c++2a -stdlib=libc++ -fimplicit-modules -fimplicit-module-maps -fprebuilt-module-path=. player.cpp test.cpp -fmodules-ts

clang++ -std=c++2a -stdlib=libc++ -fimplicit-modules -fimplicit-module-maps -fprebuilt-module-path=. main.cpp helloworld.cpp -fmodules-ts



clang++ -std=c++2a -c player.cpp -stdlib=libc++ -fmodules -fbuiltin-module-map -fmodules-ts -Xclang -emit-module-interface -o player.pcm


clang++ test.cpp athlete.cpp gamelog.cpp league.cpp team.cpp roster.cpp -std=c++20


```