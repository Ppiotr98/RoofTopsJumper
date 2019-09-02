#include "Game.h"
#include "VertexBufferLayout.h"

#include <fstream>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tinyobjloader-2.0-rc1/tiny_obj_loader.h"

Game::Game()
	: camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{

//	std::string inputfile = "res/models/buildings/buildings.obj";
//	tinyobj::attrib_t attrib;
//	std::vector<tinyobj::shape_t> shapes;
//	std::vector<tinyobj::material_t> materials;
//
//	std::string warn;
//	std::string err;
//
//	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());
//
//	if (!warn.empty()) {
//		std::cout << warn << std::endl;
//	}
//
//	if (!err.empty()) {
//		std::cerr << err << std::endl;
//	}
//
//	if (!ret) {
//		exit(1);
//	}
//
//	vector <float> positions2;
//
//	// Loop over shapes
//	for (size_t s = 0; s < shapes.size(); s++) {
//		// Loop over faces(polygon)
//		size_t index_offset = 0;
//		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
//			int fv = shapes[s].mesh.num_face_vertices[f];
//
//			// Loop over vertices in the face.
//			for (size_t v = 0; v < fv; v++) {
//				// access to vertex
//				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
//				positions2.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
//				positions2.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
//				positions2.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
//				positions2.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
//				positions2.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
//			}
//			index_offset += fv;
//
//			// per-face material
//			shapes[s].mesh.material_ids[f];
//		}
//	}
//
//	verticesCount = positions2.size() / 5;



	//std::vector< glm::vec3 > vertices;
	//std::vector< glm::vec2 > uvs;
	//std::vector< glm::vec3 > normals;
	//
	//loadOBJ("res/models/maze.obj", &vertices, &uvs, &normals);
	//
	//verticesCount = vertices.size();
	//
	//float* positions2 = new float[verticesCount * 5];
	//
	//for (int i = 0; i < verticesCount; i++)
	//{
	//	positions2[5 * i]	  = vertices[i].x;
	//	positions2[5 * i + 1] = vertices[i].y;
	//	positions2[5 * i + 2] = vertices[i].z;
	//	positions2[5 * i + 3] = uvs[i].x;
	//	positions2[5 * i + 4] = uvs[i].y;
	//}
//
//	for (int i = 0; i < positions2.size(); i+=5)
//		cout << positions2[i] << " "
//		<< positions2[i + 1] << " "
//		<< positions2[i + 2] << " "
//		<< positions2[i + 3] << " "
//		<< positions2[i + 4] << " "
//		<< endl;

	camPosition = glm::vec3(0.f, 0.f, 1.f);
	worldUp = glm::vec3(0.f, 1.f, 0.f);
	camFront = glm::vec3(0.f, 0.f, -1.f);
	camera.setPosition(glm::vec3(-2478.48f, 550.774f, 57.4234f));

	fov = 90.0f;
	nearPlane = 0.1f;
	farPlane = 1000.f;

	firstMouse = true;

	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	m_VAO = new VertexArray;

	VertexBuffer* m_VertexBuffer = new VertexBuffer("res/models/buildings/buildings.obj");
	
	VertexBufferLayout VertexLayout;
	VertexLayout.Push<float>(3);
	VertexLayout.Push<float>(2);
	//VertexLayout.Push<float>(3);
	
	m_VAO->AddBuffer(m_VertexBuffer, &VertexLayout);
	
	m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
	m_Texture1 = std::make_unique<Texture>("res/textures/kamienie.jpg");
	m_Texture2 = std::make_unique<Texture>("res/textures/tlo.jpg");

}
Game::~Game()
{	
}
void Game::OnUpdate(float deltaTime)
{
}
void Game::OnRender()
{
	Renderer renderer;

	glm::mat4 model1 = glm::mat4(1.0f);
	glm::mat4 view1 = camera.getViewMatrix();
	glm::mat4 projection1 = glm::mat4(1.0f);
	projection1 = glm::perspective(
		glm::radians(90.0f),
		800.0f / 600.0f,
		0.1f, 5000.0f);
	glm::mat4 mvp1 = projection1 * view1 * model1;

	m_Texture1->Bind(0);
	m_Shader->SetUniform1i("u_Texture", 0);
	m_Shader->Bind();
	m_Shader->SetUniformMath4f("u_MVP", mvp1);

	m_VAO->Bind();
	glDrawArrays(GL_TRIANGLES, 0, verticesCount);


//	glm::mat4 model2 = glm::scale(glm::mat4(1.0f), glm::vec3(0.02f, 0.02f, 0.02f));
//	glm::mat4 view2 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -0.2f));
//	glm::mat4 projection2 = glm::mat4(1.0f);
//	projection2 = glm::perspective(
//		glm::radians(90.0f),
//		800.0f / 600.0f,
//		0.1f, 100.0f);
//	glm::mat4 mvp2 = projection2 * view2 * model2;
//	
//	m_Texture2->Bind(0);
//	m_Shader->SetUniform1i("u_Texture", 0);
//	m_Shader->Bind();
//	m_Shader->SetUniformMath4f("u_MVP", mvp2);
//	
//	m_VAO->Bind();
//	glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}
void Game::Events(GLFWwindow* window)
{
	KeyboardEvents(window);
	MouseEvents(window);
	camera.updateInput(-1, mouseOffsetX, mouseOffsetY);
}
void Game::KeyboardEvents(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.move(FORWARD);
		if(CheckForCollisions())
			camera.move(BACKWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.move(BACKWARD);
		if (CheckForCollisions())
			camera.move(FORWARD);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.move(LEFT);
		if (CheckForCollisions())
			camera.move(RIGHT);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.move(RIGHT);
		if (CheckForCollisions())
			camera.move(LEFT);
	}
}
void Game::MouseEvents(GLFWwindow* window)
{
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (firstMouse)
	{
		lastMouseX = mouseX;
		lastMouseY = mouseY;
		firstMouse = false;
	}

	//Calc offset
	mouseOffsetX = mouseX - lastMouseX;
	mouseOffsetY = lastMouseY - mouseY;

	//Set last X and Y
	lastMouseX = mouseX;
	lastMouseY = mouseY;
}
bool Game::CheckForCollisions()
{
	glm::vec4 area1a(-0.7f, -0.7f, -0.7f, -0.7f);
	glm::vec4 area1b(0.7f, 0.7f, 0.7f, 0.7f);
	glm::vec4 area2a(camera.getPosition(), 1.0f);
	glm::vec4 area2b(camera.getPosition(), 1.0f);

	if ( (((area1a.x <= area2a.x) && (area2a.x <= area1b.x)) ||
		((area1a.x <= area2b.x) && (area2b.x <= area1b.x))) &&

		(((area1a.y <= area2a.y) && (area2a.y <= area1b.y)) ||
		((area1a.y <= area2b.y) && (area2b.y <= area1b.y))) &&

			(((area1a.z <= area2a.z) && (area2a.z <= area1b.z)) ||
		((area1a.z <= area2b.z) && (area2b.z <= area1b.z))))
		return true;
	else
		return false;
}
bool Game::loadOBJ(
	const char* path,
	std::vector < glm::vec3 >* out_vertices,
	std::vector < glm::vec2 >* out_uvs,
	std::vector < glm::vec3 >* out_normals
)
{ 
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	ifstream stream(path);
	if (!stream.is_open()) {
		cout <<"Impossible to open the file!" << endl;
		return false;
	}

	while (!stream.eof()) {

		string lineHeader;
		stream >> lineHeader;

		if (lineHeader == "v")
		{
			glm::vec3 vertex;
			stream >> vertex.x;
			stream >> vertex.y;
			stream >> vertex.z;

			temp_vertices.push_back(vertex);
		}
		else if (lineHeader == "vt")
		{
			glm::vec2 uv;
			stream >> uv.x;
			stream >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (lineHeader == "vn")
		{
			glm::vec3 normal;
			stream >> normal.x;
			stream >> normal.y;
			stream >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (lineHeader == "f")
		{
			string line;
			getline(stream, line);

			unsigned int index = 0;
			string numbers = "";
			for (; index < line.length(); ) 
			{
				numbers = "";
				for (++index; index < line.length() && line[index] != '/' && !isspace(line[index]); index++)
					numbers += line[index];
				vertexIndices.push_back(stoi(numbers) - 1);
				if (index >= line.length()) 
					break;
				if (isspace(line[index]))
					continue;

				numbers = "";
				for (++index; index < line.length() && line[index] != '/' && !isspace(line[index]); index++)
					numbers += line[index];
				if(numbers != "")
					uvIndices.push_back(stoi(numbers) - 1);
				if (index >= line.length())
					break;
				if (isspace(line[index]))
					continue;

				numbers = "";
				for (++index; index < line.length() && line[index] != '/' && !isspace(line[index]); index++)
					numbers += line[index];
				normalIndices.push_back(stoi(numbers) - 1);
			}
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex];
		out_vertices->push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex];
		out_uvs->push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex];
		out_normals->push_back(normal);
	}
}