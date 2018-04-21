docker network create --driver overlay --attachable faasinate
cd watchdog
./build.sh
docker build -t catservice .
docker service rm catservice ; docker service create --network=faasinate --name catservice catservice
cd ..
cd gateway
docker build -t server .;
docker rm -f server;
docker run  -v /var/run/docker.sock:/var/run/docker.sock --name server -p 8080:8080 -p 8000:8000 --network=faasinate server