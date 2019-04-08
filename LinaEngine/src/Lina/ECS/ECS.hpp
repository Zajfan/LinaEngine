/*
Author: Inan Evin - Thanks to the lectures & contributions of Benny Bobaganoosh, thebennybox.
www.inanevin.com

Copyright 2018 Inan Evin

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions 
and limitations under the License.

Class: ECS
Timestamp: 4/8/2019 5:43:51 PM

*/

#pragma once

#ifndef ECS_HPP
#define ECS_HPP

#include "ECSSystem.hpp"

namespace LinaEngine
{
	class ECS
	{
	public:

		ECS() {}
		~ECS();
		
		/* Entity Creator */
		EntityHandle MakeEntity(BaseECSComponent** components, const uint32* componentIDs, size_t numComponents);
		
		/* Removes an entity from the sys */
		void RemoveEntity(EntityHandle handle);

		template<class... Args> 
		EntityHandle MakeEntity(Args...args)
		{
			const size_t n = sizeof...(Args);
			BaseECSComponent* components[n] = { nullptr };
			uint32 componentIDs[n] = { 0 };

			int index = 0;

			for (auto type : args)
			{
				components[index] = &type;
				componentIDs[index] = type::ID;
				index++;
			}

			return MakeEntity(components, componentIDs, n);
		}

		template<class A, class B, class C>
		EntityHandle MakeEntity(A& c1, B& c2, C& c3)
		{
			BaseECSComponent* components[] = { &c1, &c2, &c3 };
			uint32 componentIDs[] = { A::ID, B::ID, C::ID };
			return MakeEntity(components, componentIDs, 3);
		}


		/* Adds component to an entity */
		template<class Component>
		FORCEINLINE void AddComponent(EntityHandle entity, Component* component)
		{
			AddComponentInternal(entity, HandleToEntity(entity), Component::ID, component);
		}

		/* Removes component from an entity */
		template<class Component>
		bool RemoveComponent(EntityHandle entity)
		{
			return RemoveComponentInternal(entity, Component::ID);
		}

		/* Gets the typed component out of the entity. */
		template<class Component>
		Component* GetComponent(EntityHandle entity)
		{
			return (Component*)GetComponentInternal(HandleToEntity(entity), components[Component::ID], Component::ID);
		}

		/* System Tick */
		void UpdateSystems(ECSSystemList& systems, float delta);
		

	private:

		/* Map of id & for each id a seperate array for each comp type */
		LinaMap<uint32, LinaArray<uint8>> components;
		
		/* Entities with pair ids. */
		LinaArray<LinaPair<uint32, LinaArray<LinaPair<uint32, uint32>>>*> entities;

		/* Converts an entity handle to raw type */
		FORCEINLINE LinaPair<uint32, LinaArray<LinaPair<uint32, uint32> > >* HandleToRawType(EntityHandle handle)
		{
			return (LinaPair<uint32, LinaArray<LinaPair<uint32, uint32> > >*)handle;
		}

		/* Pulls the index out of an entity handle. */
		FORCEINLINE uint32 HandleToEntityIndex(EntityHandle handle)
		{
			return HandleToRawType(handle)->first;
		}

		/* Converts an entity handle to entity type */
		FORCEINLINE LinaArray<LinaPair<uint32, uint32> >& HandleToEntity(EntityHandle handle)
		{
			return HandleToRawType(handle)->second;
		}

		void DeleteComponent(uint32 componentID, uint32 index);
		bool RemoveComponentInternal(EntityHandle, uint32 componentID);
		void AddComponentInternal(EntityHandle handle, LinaArray<LinaPair<uint32, uint32>>& entity, uint32 componentID, BaseECSComponent* component);
		BaseECSComponent* GetComponentInternal(LinaArray<LinaPair<uint32, uint32>>& entityComponents, LinaArray<uint8>& arr, uint32 componentID);
		void UpdateSystemMultipleComponentsInternal(uint32 index, ECSSystemList& systems, float delta, const LinaArray<uint32>& componentTypes, LinaArray<BaseECSComponent*>& componentParam, LinaArray<LinaArray<uint8>*>& componentArrays);
		uint32 FindLeastCommonComponent(const LinaArray<uint32>& componentTypes, const LinaArray<uint32>& componentFlags);

		NULL_COPY_AND_ASSIGN(ECS);
	};

}


#endif