// Add you device OpenCL code
__kernel void vecAdd(
	__global double * inputA, 
	__global double * inputB, 
	__global double * outputC) { 
	size_t idx = get_global_id(0);

	outputC[idx] = inputA[idx] + inputB[idx];
}
