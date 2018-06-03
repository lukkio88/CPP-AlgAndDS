// Host code

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <memory.h>
#include <vector>

#include <iostream>
#include <string>
#include <Windows.h>
#include "CL\cl.h"

const char* TranslateOpenCLError(cl_int errorCode)
{
	switch (errorCode)
	{
	case CL_SUCCESS:                            return "CL_SUCCESS";
	case CL_DEVICE_NOT_FOUND:                   return "CL_DEVICE_NOT_FOUND";
	case CL_DEVICE_NOT_AVAILABLE:               return "CL_DEVICE_NOT_AVAILABLE";
	case CL_COMPILER_NOT_AVAILABLE:             return "CL_COMPILER_NOT_AVAILABLE";
	case CL_MEM_OBJECT_ALLOCATION_FAILURE:      return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
	case CL_OUT_OF_RESOURCES:                   return "CL_OUT_OF_RESOURCES";
	case CL_OUT_OF_HOST_MEMORY:                 return "CL_OUT_OF_HOST_MEMORY";
	case CL_PROFILING_INFO_NOT_AVAILABLE:       return "CL_PROFILING_INFO_NOT_AVAILABLE";
	case CL_MEM_COPY_OVERLAP:                   return "CL_MEM_COPY_OVERLAP";
	case CL_IMAGE_FORMAT_MISMATCH:              return "CL_IMAGE_FORMAT_MISMATCH";
	case CL_IMAGE_FORMAT_NOT_SUPPORTED:         return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
	case CL_BUILD_PROGRAM_FAILURE:              return "CL_BUILD_PROGRAM_FAILURE";
	case CL_MAP_FAILURE:                        return "CL_MAP_FAILURE";
	case CL_MISALIGNED_SUB_BUFFER_OFFSET:       return "CL_MISALIGNED_SUB_BUFFER_OFFSET";                          //-13
	case CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:    return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";   //-14
	case CL_COMPILE_PROGRAM_FAILURE:            return "CL_COMPILE_PROGRAM_FAILURE";                               //-15
	case CL_LINKER_NOT_AVAILABLE:               return "CL_LINKER_NOT_AVAILABLE";                                  //-16
	case CL_LINK_PROGRAM_FAILURE:               return "CL_LINK_PROGRAM_FAILURE";                                  //-17
	case CL_DEVICE_PARTITION_FAILED:            return "CL_DEVICE_PARTITION_FAILED";                               //-18
	case CL_KERNEL_ARG_INFO_NOT_AVAILABLE:      return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";                         //-19
	case CL_INVALID_VALUE:                      return "CL_INVALID_VALUE";
	case CL_INVALID_DEVICE_TYPE:                return "CL_INVALID_DEVICE_TYPE";
	case CL_INVALID_PLATFORM:                   return "CL_INVALID_PLATFORM";
	case CL_INVALID_DEVICE:                     return "CL_INVALID_DEVICE";
	case CL_INVALID_CONTEXT:                    return "CL_INVALID_CONTEXT";
	case CL_INVALID_QUEUE_PROPERTIES:           return "CL_INVALID_QUEUE_PROPERTIES";
	case CL_INVALID_COMMAND_QUEUE:              return "CL_INVALID_COMMAND_QUEUE";
	case CL_INVALID_HOST_PTR:                   return "CL_INVALID_HOST_PTR";
	case CL_INVALID_MEM_OBJECT:                 return "CL_INVALID_MEM_OBJECT";
	case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:    return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
	case CL_INVALID_IMAGE_SIZE:                 return "CL_INVALID_IMAGE_SIZE";
	case CL_INVALID_SAMPLER:                    return "CL_INVALID_SAMPLER";
	case CL_INVALID_BINARY:                     return "CL_INVALID_BINARY";
	case CL_INVALID_BUILD_OPTIONS:              return "CL_INVALID_BUILD_OPTIONS";
	case CL_INVALID_PROGRAM:                    return "CL_INVALID_PROGRAM";
	case CL_INVALID_PROGRAM_EXECUTABLE:         return "CL_INVALID_PROGRAM_EXECUTABLE";
	case CL_INVALID_KERNEL_NAME:                return "CL_INVALID_KERNEL_NAME";
	case CL_INVALID_KERNEL_DEFINITION:          return "CL_INVALID_KERNEL_DEFINITION";
	case CL_INVALID_KERNEL:                     return "CL_INVALID_KERNEL";
	case CL_INVALID_ARG_INDEX:                  return "CL_INVALID_ARG_INDEX";
	case CL_INVALID_ARG_VALUE:                  return "CL_INVALID_ARG_VALUE";
	case CL_INVALID_ARG_SIZE:                   return "CL_INVALID_ARG_SIZE";
	case CL_INVALID_KERNEL_ARGS:                return "CL_INVALID_KERNEL_ARGS";
	case CL_INVALID_WORK_DIMENSION:             return "CL_INVALID_WORK_DIMENSION";
	case CL_INVALID_WORK_GROUP_SIZE:            return "CL_INVALID_WORK_GROUP_SIZE";
	case CL_INVALID_WORK_ITEM_SIZE:             return "CL_INVALID_WORK_ITEM_SIZE";
	case CL_INVALID_GLOBAL_OFFSET:              return "CL_INVALID_GLOBAL_OFFSET";
	case CL_INVALID_EVENT_WAIT_LIST:            return "CL_INVALID_EVENT_WAIT_LIST";
	case CL_INVALID_EVENT:                      return "CL_INVALID_EVENT";
	case CL_INVALID_OPERATION:                  return "CL_INVALID_OPERATION";
	case CL_INVALID_GL_OBJECT:                  return "CL_INVALID_GL_OBJECT";
	case CL_INVALID_BUFFER_SIZE:                return "CL_INVALID_BUFFER_SIZE";
	case CL_INVALID_MIP_LEVEL:                  return "CL_INVALID_MIP_LEVEL";
	case CL_INVALID_GLOBAL_WORK_SIZE:           return "CL_INVALID_GLOBAL_WORK_SIZE";                           //-63
	case CL_INVALID_PROPERTY:                   return "CL_INVALID_PROPERTY";                                   //-64
	case CL_INVALID_IMAGE_DESCRIPTOR:           return "CL_INVALID_IMAGE_DESCRIPTOR";                           //-65
	case CL_INVALID_COMPILER_OPTIONS:           return "CL_INVALID_COMPILER_OPTIONS";                           //-66
	case CL_INVALID_LINKER_OPTIONS:             return "CL_INVALID_LINKER_OPTIONS";                             //-67
	case CL_INVALID_DEVICE_PARTITION_COUNT:     return "CL_INVALID_DEVICE_PARTITION_COUNT";                     //-68
																												//    case CL_INVALID_PIPE_SIZE:                  return "CL_INVALID_PIPE_SIZE";                                  //-69
																												//    case CL_INVALID_DEVICE_QUEUE:               return "CL_INVALID_DEVICE_QUEUE";                               //-70    

	default:
		return "UNKNOWN ERROR CODE";
	}
}

void LogError(const char* str, ...)
{
	if (str)
	{
		va_list args;
		va_start(args, str);

		vfprintf(stderr, str, args);

		va_end(args);
	}
}

int ReadSourceFromFile(const char* fileName, char** source, size_t* sourceSize)
{
	int errorCode = CL_SUCCESS;

	FILE* fp = NULL;
	fopen_s(&fp, fileName, "rb");
	if (fp == NULL)
	{
		LogError("Error: Couldn't find program source file '%s'.\n", fileName);
		errorCode = CL_INVALID_VALUE;
	}
	else {
		fseek(fp, 0, SEEK_END);
		*sourceSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		*source = new char[*sourceSize];
		if (*source == NULL)
		{
			LogError("Error: Couldn't allocate %d bytes for program source from file '%s'.\n", *sourceSize, fileName);
			errorCode = CL_OUT_OF_HOST_MEMORY;
		}
		else {
			fread(*source, 1, *sourceSize, fp);
		}
	}
	return errorCode;
}

void runCL(double * a, double * b, double * c, const int & n) {

	cl_int err;
	cl_uint numEntries;
	cl_uint numPlatforms;

	err = clGetPlatformIDs(0, nullptr, &numPlatforms);
	//check err
	std::vector<cl_platform_id> platform(numPlatforms);
	err = clGetPlatformIDs(numPlatforms, &platform[0], nullptr);

	//Let's print the platforms
	size_t strLen;
	for (auto i = 0; i < numPlatforms; ++i) {
		err = clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, 0, nullptr, &strLen);
		std::cout << "strLen = " << strLen << std::endl;
		//Check err
		std::vector<char> platformName(strLen);
		err = clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, strLen, &platformName[0], nullptr);
		std::cout << "Platform[" << i << "] = " << std::string(platformName.data()) << std::endl;
	}

	//We now know what the platforms are let's pick a specific device

	cl_uint numDevices;
	cl_device_id device;

	err = clGetDeviceIDs(platform[0], CL_DEVICE_TYPE_GPU, 0, nullptr, &numDevices);
	//check err
	std::vector<cl_device_id> deviceId(numDevices);
	err = clGetDeviceIDs(platform[0], CL_DEVICE_TYPE_GPU, numDevices, &deviceId[0], nullptr);

	for (auto i = 0; i < numDevices; ++i) {

		err = clGetDeviceInfo(deviceId[0], CL_DEVICE_NAME, 0, nullptr, &strLen);
		//check err
		std::vector<char> deviceName(strLen);
		err = clGetDeviceInfo(deviceId[0], CL_DEVICE_NAME, strLen, &deviceName[0], nullptr);
		std::cout << "device[" << i << "] = " << std::string(deviceName.data()) << std::endl;

	}

	//Now I know the device, I can create context and commant queuq

	cl_context context;
	cl_command_queue cmd_queue;

	context = clCreateContext(0, 1, &deviceId[0], nullptr, nullptr, nullptr);
	cmd_queue = clCreateCommandQueue(context, deviceId[0], 0, nullptr);

	//Let's allocate memory
	size_t bufferSize = sizeof(double)*n;
	cl_mem a_mem = clCreateBuffer(context, CL_MEM_READ_ONLY, bufferSize, nullptr, nullptr);
	err = clEnqueueWriteBuffer(cmd_queue, a_mem, CL_TRUE, 0, bufferSize, (void*)a, 0, nullptr, nullptr);

	if (CL_SUCCESS != err) {
		std::cout << TranslateOpenCLError(err) << std::endl;
	}

	cl_mem b_mem = clCreateBuffer(context, CL_MEM_READ_ONLY, bufferSize, nullptr, nullptr);
	err |= clEnqueueWriteBuffer(cmd_queue, b_mem, CL_TRUE, 0, bufferSize, (void*)b, 0, nullptr, nullptr);

	cl_mem c_mem = clCreateBuffer(context, CL_MEM_READ_WRITE, bufferSize, nullptr, nullptr);

	if (CL_SUCCESS != err) {
		std::cout << TranslateOpenCLError(err) << std::endl;
	}

	clFinish(cmd_queue);

	//Now let's create the program (compiling kernels)
	cl_program program[1];
	cl_kernel kernel[1];

	const char * filename = "device.cl";
	char* source = NULL;
	size_t src_size = 0;
	err = ReadSourceFromFile(filename, &source, &src_size);
	program[0] = clCreateProgramWithSource(context, 1, (const char**)&source, nullptr, &err);
	err = clBuildProgram(program[0], 1, deviceId.data(), nullptr, nullptr, nullptr);
	if (CL_SUCCESS != err) {
		std::cout << "Error in clBuildProgram" << std::endl;
		std::cout << TranslateOpenCLError(err) << std::endl;
	}

	kernel[0] = clCreateKernel(program[0], "vecAdd", &err);

	//Setting kernel args
	err = clSetKernelArg(kernel[0], 0, sizeof(cl_mem), &a_mem);
	err |= clSetKernelArg(kernel[0], 1, sizeof(cl_mem), &b_mem);
	err |= clSetKernelArg(kernel[0], 2, sizeof(cl_mem), &c_mem);
	if (CL_SUCCESS != err) {
		std::cout << "Error in clSetKernelArg" << std::endl;
	}

	//Actual execution
	size_t globalWorkSize = n;
	err = clEnqueueNDRangeKernel(cmd_queue, kernel[0], 1, nullptr, &globalWorkSize, nullptr, 0, nullptr, nullptr);

	clFinish(cmd_queue);

	err = clEnqueueReadBuffer(cmd_queue, c_mem, CL_TRUE, 0, bufferSize, c, 0, nullptr, nullptr);
	clFinish(cmd_queue);

	//Teardown

	clReleaseCommandQueue(cmd_queue);
	clReleaseContext(context);
}

int main(int argc, char **argv) {
	//stuff before running openCL

	const int n = 32;

	std::vector<double> a(n);
	std::vector<double> b(n);
	double * c = new double[n];

	for (auto i = 0; i < n; ++i) {
		a[i] = static_cast<double>(i + 1);
		b[i] = static_cast<double>(n - i - 1);
	}

	runCL(a.data(), b.data(), c, n);
	//stuff after running openCL
	for (auto i = 0; i < n; ++i)
		std::cout << "res[" << i << "] = " << c[i] << std::endl;
	return 0;
}