/*
 * @Author: BOICHARD Hugo 
 * @Date: 2021-12-07 17:30:01 
 * @Last Modified by:   Boichard Hugo 
 * @Last Modified time: 2021-12-07 17:30:01 
 */

#include "Application.hpp"
#include "Constants.hpp"

int main()
{
	Application application;
	if (!application.Init())
		return ERROR_RETURN;
	application.Loop();
	return SUCCESS_RETURN;
}
