FROM dipendrabana/basicpython:latest
ENV http_proxy "http://172.31.1.3:8080"
ENV https_proxy "http://172.31.1.3:8080"
WORKDIR /server/
COPY app .
RUN  pip install -r requirements.txt
EXPOSE 8080
EXPOSE 8000
ENV http_proxy ""
ENV https_proxy ""
CMD ["python", "app.py"]