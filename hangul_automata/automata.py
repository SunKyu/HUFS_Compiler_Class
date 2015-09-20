#-*- coding:utf-8 -*-
import sys
from collections import deque

ja= "ㄱㄴㄷㄹㅁㅂㅅㅇㅈㅊㅍㅌㅋㅎㅃㅉㄸㄲㅆ"
mo = "ㅏㅑㅓㅕㅗㅛㅜㅡㅣㅐㅔㅒㅖ"
state = "start"
buf = deque( [])
intext = ""
def start(char):
    global buf
    global state
    if char in ja:
        buf.append(char)
        state = "j"
    else:
        buf.append(char)
        print ("/" , end="")
        while len(buf) !=0:
            print (buf.popleft(), end=" ")
        state = "start"

def j(char):
    global buf
    global state
    if char in mo:
        buf.append(char)
        state= "jm"

def jm(char):
    global buf
    global state
    if char in ja:
        buf.append(char)
        state = "jmj"
    elif char in mo:
        buf.append(char)
        state = "jmm"
    else:
        buf.append(char)
        print ("/" , end="")
        while len(buf) !=0:
            print (buf.popleft(), end=" ")
        state = "start"
def jmj(char):
    global buf
    global state
    if char in ja:
        buf.append(char)
        state = "jmxj"
    elif char in mo:
        print ("/" , end="")
        while len(buf) !=1:
            print (buf.popleft(), end=" ")
        buf.append(char)
        state = "jm"
    else:
        buf.append(char)
        print ("/" , end="")
        while len(buf) !=0:
            print (buf.popleft(), end=" ")
        state = "start"

def jmm(char):
    global buf
    global state
    if char in ja:
        buf.append(char)
        state = "jmxj"
    else:
        buf.append(char)
        print ("/" , end="")
        while len(buf) !=0:
            print (buf.popleft(), end=" ")
        state = "start"

def jmxj(char):
    global buf
    global state
    if char in ja:
        print ("/" , end="")
        while len(buf) !=0:
            print (buf.popleft(), end=" ")
        buf.append(char)
        state = "j"
    elif char in mo:
        print ("/" , end="")
        while len(buf) !=1:
            print (buf.popleft(), end=" ")
        buf.append(char)
        state = "jm"
    else:
        buf.append(char)
        print ("/" , end="")
        while len(buf) !=0:
            print (buf.popleft(), end=" ")
        state = "start"
        

states = {
        "start" : start,
        "j" : j,
        "jm" : jm,
        "jmm" : jmm,
        "jmj" : jmj,
        "jmxj" : jmxj,
        }
    
def run():
    global buf
    global state
    state = "start"
    for i in intext:
        states[state](i)

if __name__ == "__main__":
    with open(sys.argv[1], "r") as f:
        for i in f.readlines():
            intext+=i.rstrip('\n')
    run()

