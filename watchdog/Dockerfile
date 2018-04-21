FROM dipendrabana/basicpython
ENTRYPOINT []

COPY ./fwatchdog /usr/bin/fwatchdog
COPY ./Function.py .
ENV fprocess 'python Function.py'


EXPOSE 8080
CMD ["/usr/bin/fwatchdog"]