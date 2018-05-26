import requests 
from flask import Flask, request, redirect
import docker
from prometheus_client import Counter, start_http_server
app = Flask(__name__)
c = Counter('my_requests_total', 'HTTP Failures')

wel = 'hello'

@app.route('/')
def welcome():
	return wel

@app.route('/system/alert', methods = ['POST', 'GET'])
def alert():
	global wel
	wel = request.data
	client = docker.from_env()
	sm = client.services
	s = sm.get('server')
	count = s.attrs['Spec']['Mode']['Replicated']['Replicas']
	replicamode = docker.types.ServiceMode('replicated', replicas=count+1)
	s.update(mode = replicamode)
	return 200
	


@app.route('/metrics')
def metric():
	return redirect('http://localhost:8000');

@app.route('/functions/<path:url>', methods = ['POST'])
def prints(url):
	if request.method == 'POST':
		c.inc();
		r = requests.post('http://'+url+':8080/', headers={'content-type': 'text/plain'}, data = request.data);
		return r.content;
	else:
		return 'Bad Request! POST must have content.'


if __name__ == '__main__':
	start_http_server(8000);
	app.run(host='0.0.0.0',port=8080)