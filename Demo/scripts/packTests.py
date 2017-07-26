#!/usr/bin/env python
from subprocess import call
import shutil
from shutil import copyfile
import os

tests = ["AltBlckQ", "AltPollQ", "blocktim", "countsem", "dead", "EventGroupsDemo", "flop", "integer", "QPeek", "QueueSet", "recmutex", "semtest", "TaskNotify", "AltBlock", "AltQTest", "BlockQ", "crhook", "dynamic", "GenQTest", "PollQ", "QueueOverwrite", "QueueSetPolling", "sp_flop", "test1"]



dirs = ["bin"]
for dirName in dirs:
	#if  os.path.exists(dirName):
	#	shutil.rmtree(dirName)

	if not os.path.exists(dirName):
		os.makedirs(dirName)



def doIt(arch):
	originalPath = os.environ["PATH"] 
	os.environ["PATH"] = "/opt/" + arch + "/bin:" + originalPath
	for test in tests:
		print(test)
		assert(call(["make", "-C", "../" + test, "clean", "all", "ARCH=" + arch]) == 0)
		copyfile("../" + test + "/bin/freeRTOS_demo.elf", "bin/" + test + "_" + arch + ".elf")
		copyfile("../" + test + "/bin/freeRTOS_demo.hex", "bin/" + test + "_" + arch + ".hex")
		copyfile("../" + test + "/bin/freeRTOS_demo.asm", "bin/" + test + "_" + arch + ".asm")

	os.environ["PATH"]  = originalPath

doIt("rv32i")
doIt("rv32im")

print "SUCCESS"
