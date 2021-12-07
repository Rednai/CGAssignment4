/*
 * @Author: BOICHARD Hugo 
 * @Date: 2021-12-07 17:31:01 
 * @Last Modified by:   Boichard Hugo 
 * @Last Modified time: 2021-12-07 17:31:01 
 */

#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Model
{
public:
	virtual ~Model();
	virtual bool Init();
	virtual void Draw();
protected:
	unsigned int VAO,
		VBO,
		shaderProgram,
		triangleCount,
		vertexShader,
		fragmentShader = 0;
	vector<float> verticesData;
	string vertexShaderSource;
	string fragmentShaderSource;
};
