import requests 
from flask import Flask, request
from prometheus_client import Counter, start_http_server
app = Flask(__name__)
c = Counter('my_requests_total', 'HTTP Failures')
@app.route('/')
def welcome():
	return 'hello'

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