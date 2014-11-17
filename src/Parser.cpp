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

Parser::Parser()
{
}

Mesh Parser::parse(std::string file)
{
	std::vector<float> _points;
	std::vector<float> _normals;
	std::vector<std::string> faces;
	std::string line;
	std::ifstream myfile(file);
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			if (line[0] == 'v')
			{
				std::string v, x, y, z;
				std::istringstream iss(line);
				iss >> v >> x >> z >> y;
				_points.push_back(::atof(x.c_str()));
				_points.push_back(::atof(y.c_str()));
				_points.push_back(::atof(z.c_str()));
			}
			if (line[0] == 'v' && line[1] == 'n')
			{
				std::string v, x, y, z;
				std::istringstream iss(line);
				iss >> v >> x >> z >> y;
				_normals.push_back(::atof(x.c_str()));
				_normals.push_back(::atof(y.c_str()));
				_normals.push_back(::atof(z.c_str()));
			}
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
		myfile.close();
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
		// Find the index of the two slashes
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

Parser::~Parser()
{
}
