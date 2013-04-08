// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include "../Utilities/utilities.h" 
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <windows.h>


GLuint vboId;
Shaders myShaders;

float i=0.0;
Vertex verticesData[3];
Vector4  rez, myVector1, myVector2, myVector, m1,m2,m3;
Matrix myMatr, myMatr2;
char* pointer = 0;
int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data (heap)
	
	verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;
	verticesData[0].color.x =1.0f;  verticesData[0].color.y =  0.0f; verticesData[0].color.z =  0.0f; 
	verticesData[1].color.x =  0.0f;  verticesData[1].color.y =  1.0f;  verticesData[1].color.z =  0.0f;  
	verticesData[2].color.x =  0.0f; verticesData[2].color.y =  0.0f; verticesData[2].color.z =  1.0f;
	
	


	glGenBuffers(1, &vboId); //buffer object name generation
	glBindBuffer(GL_ARRAY_BUFFER, vboId); //buffer object binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW); //creation and initializion of buffer onject storage
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	
	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

	
}

void Draw ( ESContext *esContext )
{
	int co=0;
	glClear(GL_COLOR_BUFFER_BIT);
	

	glUseProgram(myShaders.program);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	


	if(myShaders.positionAttribute != -1) //attribute passing to shader, for uniforms use glUniform1f(time, deltaT); glUniformMatrix4fv( m_pShader->matrixWVP, 1, false, (GLfloat *)&rotationMat );
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);

		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
		char * i=0;

		glEnableVertexAttribArray(myShaders.colorAttribute);

		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE,sizeof(Vertex),i+sizeof(Vector3) );

		
	}


	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
	
}

void Update ( ESContext *esContext, float deltaTime )
{
	myVector1.x=verticesData[1].pos.x;  //Change position of Vertices
	myVector1.y=verticesData[1].pos.y;
	myVector1.z=verticesData[1].pos.z;
	rez=myMatr.SetRotationY(0.01)*myVector1;
	verticesData[1].pos.x=rez.x;
	verticesData[1].pos.y=rez.y;
	verticesData[1].pos.z=rez.z;

	
	myVector2.x=verticesData[2].pos.x;
	myVector2.y=verticesData[2].pos.y;
	myVector2.z=verticesData[2].pos.z;
	rez=myMatr.SetRotationY(0.01)*myVector2;
	verticesData[2].pos.x=rez.x;
	verticesData[2].pos.y=rez.y;
	verticesData[2].pos.z=rez.z;
	
	
	//buffer object
	glGenBuffers(1, &vboId); //buffer object name generation
	glBindBuffer(GL_ARRAY_BUFFER, vboId); //buffer object binding
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW); //creation and initializion of buffer onject storage
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;
	
    esInitContext ( &esContext );
	
	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
	
	if ( Init ( &esContext ) != 0 ){
		
		return 0;}
	
	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	
	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();
	
	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

