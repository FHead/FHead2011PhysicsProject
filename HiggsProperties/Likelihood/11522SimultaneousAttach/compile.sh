#!/bin/bash
CompileRootMacro AttachLikelihoodWithInterpolation.cpp RunWithInterpolation -I../../CommonCode/include ../../CommonCode/library/*
CompileRootMacro AttachLikelihoodWithInterpolationAndSmear.cpp RunWithInterpolationAndSmear -I../../CommonCode/include ../../CommonCode/library/*
# CompileRootMacro AttachLikelihood.cpp RunWithoutInterpolation -I../../CommonCode/include ../../CommonCode/library/*

