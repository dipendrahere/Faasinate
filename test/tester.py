import requests
print('Enter file name: ');
filename = raw_input()
f = file(filename, 'r+');
cont = f.read();
d = filename.split('.');
flag = 3
if d[1] == 'cpp':
	flag = 1
elif d[1] == 'py':
	flag = 2
else:
	flag = 3
r = requests.post('http://localhost:8080/functions/catservice', data=str(flag)+cont);
f.close()
f = file('test.tex','r+');
f.write(r.content);
f.close();