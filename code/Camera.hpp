#pragma once

#include "math.hpp"
#include "Entity.hpp"

using namespace glm;

/// <summary>
/// A camera allows for rendering inside of a scene.
/// </summary>
class Camera : public Entity
{
private:

	float fov;
	float near_plane, far_plane;

	unsigned int width, height;
	float aspect_ratio;

	/// <summary>
	/// Local save of the transform before the render pass.
	/// </summary>
	glm::mat4 originalTransform;

public:

	Camera() {}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="width">width of the camera</param>
	/// <param name="height">height of the camera</param>
	/// <param name="fov">vertical field of view</param>
	/// <param name="near_plane">closest rendering plane</param>
	/// <param name="far_plane">farthest rendering plane</param>
	Camera(unsigned int width, unsigned int height, float fov = 20, float near_plane = 1, float far_plane = 15)
	{
		this->fov = fov;
		this->near_plane = near_plane;
		this->far_plane = far_plane;

		this->width = width;
		this->height = height;

		this->aspect_ratio = (float)width / height;
	}

	/// <summary>
	/// Changes camera transform matrix to its identity to allow for further rendering.
	/// </summary>
	inline void render_pass()
	{
		originalTransform = transform;
		transform = get_inverse_transform() * transform;
	}

	/// <summary>
	/// Resets the camera to its original position before a render pass.
	/// </summary>
	inline void reset()
	{
		transform = originalTransform;
	}

	/*GETTERS*/

	inline glm::mat4 get_perspective_matrix()
	{
		return glm::perspective(fov, aspect_ratio, near_plane, far_plane);
	}
	inline glm::mat4 get_inverse_transform() { return glm::inverse(transform); }
	inline float get_fov()				{ return fov;			}
	inline float get_near_plane()		{ return near_plane;	}
	inline float get_far_plane()		{ return far_plane;		}
	inline float get_aspect_ratio()		{ return aspect_ratio;	}
	inline unsigned int get_width()		{ return width;			}
	inline unsigned int get_height()	{ return height;		}
};