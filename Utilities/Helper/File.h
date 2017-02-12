#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>

#include "..\Container\Vertex.h"

namespace File {
	std::string toString(const std::string& file) {
		std::fstream f(file);
		assert(f.is_open());
		std::string string;
		std::getline(f, string, '\0');
		f.close();

		return string;
	}

	void toMesh(const std::string& file, std::vector<Vertex>& vertices, std::vector<unsigned int>& elements) {
		std::fstream f(file);
		assert(f.is_open());

		std::vector<Vector3> p;
		std::vector<Vector3> n;
		std::vector<Vector2> t;
		std::string line;
		std::getline(f, line);
		while (std::getline(f, line)) {
			if (line.substr(0,2) == "v ") {
				Vertex v;
				std::istringstream stream(line.substr(2));
				stream >> v.position.x;
				stream >> v.position.y;
				stream >> v.position.z;

				v.position.x /= 20;
				v.position.y /= 20;
				v.position.z /= 20;
				vertices.push_back(v);
			}
			else if (line.substr(0, 2) == "vn") {
				Vector3 v;
				std::istringstream stream(line.substr(3));
				stream >> v.x;
				stream >> v.y;
				stream >> v.z;
				n.push_back(v);
			}
			else if (line.substr(0, 2) == "vt") {
				Vector2 v;
				std::istringstream stream(line.substr(3));
				stream >> v.x;
				stream >> v.y;
				t.push_back(v);
			}
			else if (line.substr(0, 2) == "f ") {
				std::string p[3];
				unsigned int vert[3];
				unsigned int tex[3];
				unsigned int norm[3];

				std::replace(line.begin(), line.end(), '/', ' ');
				std::istringstream stream(line.substr(2));

				stream >> vert[0];
				stream >> tex[0];
				stream >> norm[0];
				stream >> vert[1];
				stream >> tex[1];
				stream >> norm[1];
				stream >> vert[2];
				stream >> tex[2];
				stream >> norm[2];

				for (unsigned int i = 0; i < 3; i++) {
					vert[i]--;
					tex[i]--;
					norm[i]--;

					elements.push_back(vert[i]);
					vertices[vert[i]].normal = n[norm[i]];
					vertices[vert[i]].uv = t[tex[i]];
				}
			}
		}
	}
}