#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#include "Renderer.h"
#include "Context.h"
#include "Parser.h"
#include "Mesh.h"

Rr::Parser::Parser()
{
}

Rr::Parser::~Parser()
{
}

Rr::Mesh Rr::Parser::parse(std::string file)
{
	// Points substracted from the .obj file
	std::vector<float> _points;

	// Normals substracted from the .obj file
	std::vector<float> _normals;

	// Faces substracted from the .obj file
	std::vector<std::string> faces;

	// The line which is getting read now
	std::string line;

	// The file
	std::ifstream objfile(file);

	if (objfile.is_open())
	{
		// As long as we don't reach the end of the file we read every line
		while (!objfile.eof())
		{
			getline(objfile, line);

			// It's a vertex
			if (line[0] == 'v')
			{
				std::string v, x, y, z;
				std::istringstream iss(line);
				iss >> v >> x >> z >> y;
				_points.push_back(::atof(x.c_str()));
				_points.push_back(::atof(y.c_str()));
				_points.push_back(::atof(z.c_str()));
			}

			// It's a vertex normal
			if (line[0] == 'v' && line[1] == 'n')
			{
				std::string v, x, y, z;
				std::istringstream iss(line);
				iss >> v >> x >> z >> y;
				_normals.push_back(::atof(x.c_str()));
				_normals.push_back(::atof(y.c_str()));
				_normals.push_back(::atof(z.c_str()));
			}

			// It's a face
			if (line[0] == 'f')
			{
				std::string v, f1, f2, f3;
				std::istringstream iss(line);
				iss >> v >> f1 >> f2 >> f3;
				faces.push_back(f1);
				faces.push_back(f2);
				faces.push_back(f3);
			}
		}
		objfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	// Generate the mesh based on the extracted data
	Mesh mesh = Mesh();
	std::vector<float> points;
	std::vector<float> normals;
	for (int i = 0; i < faces.size(); i += 1)
	{
		// Find the index of the two slashes in the face
		size_t slashIndex = faces[i].find('//');

		// Based on the slashes extract the vertex and normal index of the faces
		std::string vertexString = faces[i].substr(0, slashIndex);
		std::string normalString = faces[i].substr(slashIndex + 2, faces[i].length() - 1);
		int vertex = std::stoi(vertexString);
		int normal = std::stoi(normalString);

		// Minus one since .obj starts with 1 instead of 0
		vertex -= 1;
		normal -= 1;

		// Times three since every vertex exicts of three points
		vertex *= 3;
		normal *= 3;

		// Add the tree points
		points.push_back(_points[vertex + 0]);
		points.push_back(_points[vertex + 1]);
		points.push_back(_points[vertex + 2]);

		// Add the three normals
		normals.push_back(_normals[normal + 0]);
		normals.push_back(_normals[normal + 1]);
		normals.push_back(_normals[normal + 2]);
	}

	// Set the points and normals of this mesh
	mesh.setPoints(points);
	mesh.setNormals(normals);

	return mesh;
}
