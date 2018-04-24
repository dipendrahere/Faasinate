docker service rm $(docker service ls -q)
docker stop $(docker ps -aq)
docker rm -f $(docker ps -aq)

docker network create --driver overlay --attachable faasinate
cd watchdog
./build.sh
docker build -t catservice .
docker service rm catservice ; docker service create --network=faasinate --name catservice catservice
cd ..
cd gateway
docker build -t server .;
docker service rm server;
docker service create --name server --mode replicated -p 8080:8080 -p 8000:8000 --network=faasinate  server
cd ..
cd prometheus
docker build -t prometheus -f Dockerfile.prometheus .
docker build -t alertmanager -f Dockerfile.alertmanager .
docker rm -f prometheus
docker rm -f alertmanager
docker service create -p 9093:9093 --name alertmanager --network=faasinate alertmanager --config.file=/alertmanager.yml 
docker service create -p 9095:9090 --name prometheus --network=faasinate prometheus --config.file=/etc/prometheus/prometheus.yml
