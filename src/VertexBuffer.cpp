#include "VertexBuffer.h"
#include "Renderer.h"

#include <iostream>

#include "tinyobjloader-2.0-rc1/tiny_obj_loader.h"

VertexBuffer::VertexBuffer(std::string path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

	if (!warn.empty()) {
		std::cout << warn << std::endl;
	}

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}

	if (!ret) {
		exit(1);
	}

	// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) {
		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			int fv = shapes[s].mesh.num_face_vertices[f];

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				m_vertices.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
				m_vertices.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
				m_vertices.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
				m_vertices.push_back(attrib.texcoords[2 * idx.texcoord_index + 0]);
				m_vertices.push_back(attrib.texcoords[2 * idx.texcoord_index + 1]);
			}
			index_offset += fv;

			// per-face material
			shapes[s].mesh.material_ids[f];
		}
	}

	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}