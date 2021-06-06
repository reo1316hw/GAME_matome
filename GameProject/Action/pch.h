#ifndef PCH_H
#define PCH_H

#include <fstream>
#include <sstream>
#include <document.h>
#include <SDL_log.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <SDL.h>
#include <functional>
#include <unordered_map>
#include <glew.h>

#include "Math.h"
#include "BoneTransform.h"
#include "Skeleton.h"
#include "ColliderComponent.h"
#include "Game.h"
#include "PhysicsWorld.h"
#include "Collision.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Component.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "HDRRenderer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Animation.h"

#include "MeshComponent.h"
#include "InvisibleMeshComponent.h"
#include "SkeletalMeshComponent.h"

#include "SpriteComponent.h"
#include "Sprite.h"

#include "UIComponent.h"
#include "UIBase.h"
#include "HeartUI.h"

#include "ParticleComponent.h"
#include "EffectManager.h"
#include "ParticleEffectBase.h"
#include "CheckpointBoard.h"
#include "GoalLine.h"
#include "OperationExplanationBoard.h"
#include "VerticalMoveGroundExplanationBoard.h"

#include "CheckpointEffect.h"
#include "SandEffect.h"
#include "ClearEffect.h"
#include "DeathEffect.h"

#include "MatrixPalette.h"

#include "InputSystem.h"

#include "RapidJsonHelper.h"
#include "MapCreate.h"

#include "GameObject.h"
#include "GameObjectManager.h"
#include "MainCameraObject.h"
#include "Player.h"
#include "Ground.h"
#include "Glass.h"
#include "Block.h"
#include "VerticalMoveGround.h"
#include "Jump.h"
#include "LateralMoveGround.h"
#include "UpBlock.h"
#include "VerticalBlock.h"
#include "AerialBlock.h"
#include "RightBlock.h"
#include "LeftBlock.h"
#include "RightGround.h"
#include "LeftGround.h"
#include "DownBlock.h"
#include "GoalBlock.h"
#include "Respawn.h"

#include "SceneBase.h"
#include "TitleScene.h"
#include "TutorialScene.h"
#include "Stage01Scene.h"
#include "Stage02Scene.h"
#include "ContinueScene.h"
#include "GameOver.h"
#include "GameClear.h"

#include "FPS.h"

#endif