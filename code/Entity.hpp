#pragma once
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include "math.hpp"
#include <queue>

/// <summary>
/// An entity represents all the items that can be rendered and moved independently inside of the window frame.
/// </summary>
class Entity
{

protected:
	glm::vec3 position = { 0,0, 0.f };
	glm::vec3 rotation = { 0,0,0 };

	float scaleFactor = 1.f;

	glm::mat4 transform = glm::mat4(1);

	Entity* parent = nullptr;


	//Saves transforms when we perform destructive operations. Allows us to return to the last safe and true transform.
	glm::mat4 original_transform = transform;

	//A buffer of to-be-applied translations, occurring when a update on this entity is called.
	std::queue<glm::mat4> waiting_translations;

public: 

	/// <summary>
	/// Sets a new parent and resets its transformation to be 0,0,0 in regards to its parent.
	/// </summary>
	/// <param name="parent"></param>
	inline void set_parent(Entity & parent)
	{
		this->parent = &parent;

		//we set it at the parent's center.
		translate({ 0,0,0 });
	}

	void translate(glm::vec3 newPosition)
	{
		position.x = newPosition.x;
		position.y = newPosition.y;
		position.z = newPosition.z;

		glm::mat4 identity = glm::mat4(1);
		glm::mat4 t = glm::translate(identity, position);

		waiting_translations.push(t);
	}

	/// <summary>
	/// Rotates this entity.
	/// </summary>
	/// <param name="displacement">amount of rotation per axis</param>
	void rotate(glm::vec3 displacement)
	{
		rotation.x = displacement.x;
		rotation.y = displacement.y;
		rotation.z = displacement.z;

		glm::mat4 identity = glm::mat4(1);
		glm::mat4 xRot = glm::rotate(identity, rotation.x, glm::vec3(1.f, 0.f, 0.f));
		glm::mat4 yRot = glm::rotate(identity, rotation.y, glm::vec3(0.f, 1.f, 0.f));
		glm::mat4 zRot = glm::rotate(identity, rotation.z, glm::vec3(0.f, 0.f, 1.f));

		glm::mat4 t = xRot * yRot * zRot;

		waiting_translations.push(t);
	}

	void scale(float floatScale)
	{

		glm::mat4 identity = glm::mat4(1);
		glm::mat4 t = glm::scale(identity, { floatScale, floatScale, floatScale });

		waiting_translations.push(t);
	}

	void update()
	{
		while (!waiting_translations.empty())
		{
			if(parent)
				transform = original_transform;

			transform = transform * waiting_translations.front();

			if (parent)
			{
				original_transform = transform;
				transform = get_uniform_transform_matrix();
			}

			waiting_translations.pop();
		}
	}

	inline void set_transform(glm::mat4 new_transform)
	{
		transform = new_transform;
	}

	/*GETTERS*/
	inline const glm::mat4	get_transform		()		
	{
		return this->transform;
	}
	inline const glm::vec3	get_rotation		()		
	{
		return this->rotation;
	}
	inline const glm::vec3	get_position		()		
	{
		return this->position;
	}
	inline const Entity*	get_parent_entity	()
	{
		return this->parent;
	}

private:

	/// <summary>
	/// 
	/// </summary>
	/// <returns> Returns the unified transform matrix of this entity with its parent.
	/// Returns its transform if the entity doesn't have a parent</returns>
	glm::mat4 get_uniform_transform_matrix()
	{
		return parent ? parent->transform * transform : transform;
	}

};