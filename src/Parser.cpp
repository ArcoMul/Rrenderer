#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

#include "Renderer.h"
#include "Context.h"
#include "Parser.h"
#include "Triangle.h"
#include "Mesh.h"

Parser::Parser()
{
}

Mesh Parser::parse(std::string file)
{
	std::vector<float> vertices;
	std::vector<int> faces;
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
				vertices.push_back(::atof(x.c_str()));
				vertices.push_back(::atof(y.c_str()));
				vertices.push_back(::atof(z.c_str()));
			}
			if (line[0] == 'f')
			{
				std::string v, f1, f2, f3;
				std::istringstream iss(line);
				iss >> v >> f1 >> f2 >> f3;
				faces.push_back(std::stoi(f1));
				faces.push_back(std::stoi(f2));
				faces.push_back(std::stoi(f3));
			}
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}

	Mesh mesh = Mesh();

	std::vector<float> points;
	for (int i = 0; i < faces.size(); i += 3)
	{
		int face1 = (faces[i + 0] - 1) * 3;
		int face2 = (faces[i + 1] - 1) * 3;
		int face3 = (faces[i + 2] - 1) * 3;
		points.push_back(vertices[face1 + 0]);
		points.push_back(vertices[face1 + 1]);
		points.push_back(vertices[face1 + 2]);
		points.push_back(vertices[face2 + 0]);
		points.push_back(vertices[face2 + 1]);
		points.push_back(vertices[face2 + 2]);
		points.push_back(vertices[face3 + 0]);
		points.push_back(vertices[face3 + 1]);
		points.push_back(vertices[face3 + 2]);
	}

	mesh.setPoints(points);

	return mesh;
}

Parser::~Parser()
{
}
