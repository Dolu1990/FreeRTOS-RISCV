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



def doIt(arch, opt):
	originalPath = os.environ["PATH"] 
	os.environ["PATH"] = "/opt/" + arch + "/bin:" + originalPath
	for test in tests:
		print(test)
		assert(call(["make", "-C", "../" + test, "clean", "all", "ARCH=" + arch, "OPT=" + opt, "PRINT_ENABLE=no"]) == 0)
		copyfile("../" + test + "/bin/freeRTOS_demo.elf", "bin/" + test + "_" + arch + "_" + opt + ".elf")
		copyfile("../" + test + "/bin/freeRTOS_demo.hex", "bin/" + test + "_" + arch + "_" + opt +  ".hex")
		copyfile("../" + test + "/bin/freeRTOS_demo.asm", "bin/" + test + "_" + arch + "_" + opt +  ".asm")

	os.environ["PATH"]  = originalPath


doIt("rv32i", "O0")
doIt("rv32im", "O0")
doIt("rv32i", "O3")
doIt("rv32im", "O3")
print "SUCCESS"
