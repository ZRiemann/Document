#!/bin/bash

cmd_dir=$(pwd)
# cd work-dir
cd ${0%/*}

enable_dbg=0
. ../../../zsa/base.sh

prompt(){
echo_inf "
press any key to next step...
"
read pick
}

step1(){
echo_msg "
1.0 Running your first container

1.0.1 pull alpine( [ˈælˌpaɪn]) image
$ docker pull alpine

"sudo docker pull alpine
}

step2(){
prompt
echo_msg "
1.0.2 list all images on your system
$ docker images
"
sudo docker images
}

step3(){
prompt
echo_msg "
1.0.3 Docker Run
$ docker run alpine ls -l
"
sudo docker run alpine ls -l
echo_inf "
1. The Docker client contacts the Docker daemon
2. The Docker daemon checks local store if image alpine is vailable locally,
   and if not, downloads it forom Docker Store
3. The Docker daemon creates the container and then runs a command in that container.
4. The Docker deamon stream the output of the command to the Docker client
   you provided a command (ls -l)
5. try $ docker run alpine echo hello from alpine
"
sudo docker run alpine echo "hello from alpine"
}

step4(){
    prompt
    echo_msg "
1.0.4 Run in an interactive terminal(-it)
$ sudo docker run -it alpine /bin/sh
try ls -l/ uname -a
and exit
"
sudo docker run -it alpine /bin/sh
echo_inf "
1.0.5 Terminology(jargon in the Docker ecosystem)
- Images
  The file system and configuration of our application which are used to create containers.
  $ docker inspect alpine
- Containers
  Running instances of Docker images
  $ docker run <image>
  $ docker ps
- Docker daemon
  The background service running on the host that
  managers building,running,distributing Docker containers.
- Docker client
  The command line tool that allows the user to interact with the Docker daemon
- Docker store
  A registry of Docker images, where your can find trusted and enterprise ready containers,
  plugins,and Docker editions. You'll be using this later in this tutorial.
"
}

step5(){
    prompt
    echo_msg "
2.0 Webapps with Docker
2.1 Run a static website in a container
    https://github.com/docker/labs/blob/master/beginner/static-site
    $ docker run -d dockersamples/static-site
    (-d) detached mode
    $ docker stop <id>
    $ docker rm <id>
    docker run --name static-site -e AUTHOR="Your Name" -d -P dockersamples/static-site
 -d create a container with the process detached from our terminal
 -P publish all the exposed container prots to a random ports on the Docker host
 -e is how you pass environment variables to the container
 --name allow you to specify a container name
 - AUTHOR is the environment variable name and Your name is the value that you can pass
"
    sudo docker run --name static-site -e AUTHOR="Your Name" -d -P dockersamples/static-site

}
#================================================================================
# step1
# step2
# step3
# step4
step5
cd $cmd_dir
exit 0