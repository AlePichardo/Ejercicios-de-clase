/*---------------------------------------------------------*/
/* ----------------   Práctica 7 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*- Computación gráfica e interacción humano computadora  -*/
/*-------------         Grupo 4             ---------------*/
/*-------------      Visual Studio 2017       -------------*/
/*----------  Pichardo González Jenny Alejandra  ----------*/

//Teclas de movimiento
//Tecla W: Acercar		Tecla S: Alejar
//Tecla A: Izquierda	Tecla D: Derecha

#include "esfera.h"
#include "camera.h"

Esfera my_sphere(1.0);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, lightVAO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

void myData(void);
void display(void);
void getResolution(void);
void animate(void);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -5.0f,
		rotX = 0.0f;

float	sol = 0.0f,
		year = 0.0f,
		day = 0.0f,
		moon = 0.0f,
		mars_year = 0.0f,
		jupiter_year = 0.0f,

		mercurio = 0.0f,
		venus = 0.0f,
		tierra = 0.0f,
		marte = 0.0f,
		jupiter = 0.0f,
		saturno = 0.0f,
		urano = 0.0f,
		neptuno = 0.0f;


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,//
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//To configure Second Objecto to represet Light
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void animate(void)
{
	sol += 0.5f;
	mercurio += 0.9f;
	venus += 0.8;
	tierra += 0.7;
	marte += 0.6f,
	jupiter += 0.5f,
	saturno += 0.4f,
	urano += 0.3f,
	neptuno += 0.2f;
}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	//Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_light_Gouraud.vs", "shaders/shader_light_Gouraud.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	projectionShader.use();
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f); //Definimos componente de iluminación (luz x material)
	projectionShader.setVec3("lightPos", lightPos); //Asignamos posición

	// create transformations and Projection
	glm::mat4 temp01 = glm::mat4(1.0f); //Temp
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to inlcude Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix(); //Asignamos la cámara a la vista

	// pass them to the shaders}
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	//Colocar código aquí
	model = glm::rotate(model, glm::radians(sol), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 0.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();	//Sphere
	glDrawArrays(GL_TRIANGLES, 0, 36);	//Light


	//Mercurio
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-mercurio), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(3, 0, 0));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.4f, 0.7f, 0.3f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();
	model = glm::mat4(1.0f);
	
	//Venus
	model = glm::rotate(model, glm::radians(-venus), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(4, 0, 0));
	model = glm::rotate(model, glm::radians(venus), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.7f, 0.5f, 0.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();
	model = glm::mat4(1.0f);
	
	//Tierra
	model = glm::rotate(model, glm::radians(-tierra), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(5.5, 0, 0));
	model = glm::rotate(model, glm::radians(tierra), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.3f, 0.1f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();
	
	//Luna
	model = glm::rotate(model, glm::radians(-tierra * 5), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(tierra * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();
	model = glm::mat4(1.0f);

	//Marte
	model = glm::rotate(model, glm::radians(-marte), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(7, 0, 0));
	model = glm::rotate(model, glm::radians(marte), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 0.0f, 0.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Fobos
	model = glm::rotate(model, glm::radians(-marte * 5), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(marte * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Deimos
	model = temp01;
	model = glm::rotate(model, glm::radians(-marte * 6), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(0.5, 0.1, 0));
	model = glm::rotate(model, glm::radians(marte * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();
	model = glm::mat4(1.0f);

	//Jupiter
	model = glm::rotate(model, glm::radians(-jupiter), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(12, 0, 0));
	model = glm::rotate(model, glm::radians(jupiter), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 0.5f, 0.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Ío
	model = glm::rotate(model, glm::radians(-jupiter * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(jupiter * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Europa
	model = temp01;
	model = glm::rotate(model, glm::radians(-jupiter * 4), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(1.5, 0.1, 0));
	model = glm::rotate(model, glm::radians(jupiter * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Ganímedes
	model = temp01;
	model = glm::rotate(model, glm::radians(-jupiter * 5), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(1.8, -0.1, 0));
	model = glm::rotate(model, glm::radians(jupiter * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Calisto
	model = temp01;
	model = glm::rotate(model, glm::radians(-jupiter * 6), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(2.1, 0.2, 0));
	model = glm::rotate(model, glm::radians(jupiter * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();
	model = glm::mat4(1.0f);

	//Saturno
	model = glm::rotate(model, glm::radians(-saturno), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(18, 0, 0));
	model = glm::rotate(model, glm::radians(saturno), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 0.6f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Anillo 1
	model = glm::rotate(model, glm::radians(saturno * 3), glm::vec3(0.0f, 0.0f, 1.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(1.2f, 0.1f, 1.2f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Anillo 2
	model = temp01;
	model = glm::rotate(model, glm::radians(saturno * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(1, 0.1f, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Titán
	model = temp01;
	model = glm::rotate(model, glm::radians(-saturno * 6), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(saturno * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();
	model = glm::mat4(1.0f);

	//Urano
	model = glm::rotate(model, glm::radians(-urano), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(23, 0, 0));
	model = glm::rotate(model, glm::radians(urano), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.7f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Titania
	model = glm::rotate(model, glm::radians(-urano * 5), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(urano * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Oberón
	model = temp01;
	model = glm::rotate(model, glm::radians(-urano * 6), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(1.2, -0.1, 0));
	model = glm::rotate(model, glm::radians(urano * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();
	model = glm::mat4(1.0f);

	//Neptuno
	model = glm::rotate(model, glm::radians(-neptuno), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(27, 0, 0));
	model = glm::rotate(model, glm::radians(neptuno), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.55f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.5f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();

	//Tritón
	model = glm::rotate(model, glm::radians(-neptuno * 5), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Traslación
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(neptuno * 3), glm::vec3(0.0f, 1.0f, 0.0f)); //Movimiento de Rotación
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f); //Da color a la mayor parte de la figura
	projectionShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f); //Brillo de la esfera
	my_sphere.render();


	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.4f));
	lampShader.setMat4("model", model);


	glBindVertexArray(lightVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);	//Light


	//glBindVertexArray(0);

}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 7", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        // input
        // -----
        my_input(window);
		animate();

        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}