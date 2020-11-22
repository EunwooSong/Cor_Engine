#include "stdafx.h"
#include "AnimationController.h"

AnimationController::AnimationController()
{
}

AnimationController::~AnimationController()
{
}

void AnimationController::Start()
{
}

void AnimationController::Update()
{
}

void AnimationController::Render()
{
}

void AnimationController::EndScene()
{
}

void AnimationController::CheckAnimationState()
{
	
}

SpriteAnimation* AnimationController::GetCurrentAniamtion()
{
	return current_node->second->currentAnim;
}

void AnimationController::AddAnimationNode(std::string nodeName, SpriteAnimation* p_anim)
{
	if (anim_node.find(nodeName) != anim_node.end()) {
		std::cout << "[ ERROR ] Duplicated animation identifier " << std::endl;
		return;												
	}

	AnimationNode* iter = new AnimationNode();
	iter->currentAnim = p_anim;

	anim_node.insert(std::pair<std::string, AnimationNode*>(nodeName, iter));
}

void AnimationController::AddTrigger(std::string paramKey, std::string targetAnim)
{
	if (anim_node.find(targetAnim) == anim_node.end()) {
		std::cout << "[ ERROR ] Nonexistent Animation identifier " << std::endl;
	}

	StateNode<trigger> tmp;

	tmp.paramName = paramKey;
	tmp.operater = EQUALS;
	tmp.targetValue = (trigger)true;
	tmp.changeNodeName = targetAnim;

	stateType_Trigger.push_back(tmp);
}

void AnimationController::SetEntryAnimationNode(std::string targetAnim)
{
	if (anim_node.find(targetAnim) == anim_node.end()) {
		std::cout << "[ ERROR ] Nonexistent Animation identifier " << std::endl;
	}
	
	entry_node = anim_node.find(targetAnim);
}

void AnimationController::SetInt(std::string paramKey, int value)
{
	if (param_int.find(paramKey) == param_int.end()) {
		std::cout << "[ ERROR ] Nonexistent animation parameter identifier (int)" << std::endl;
		return;
	}

	param_int[paramKey] = value;
}

void AnimationController::SetFloat(std::string paramKey, float value)
{
	if (param_float.find(paramKey) == param_float.end()) {
		std::cout << "[ ERROR ] Nonexistent animation parameter identifier (float)" << std::endl;
		return;
	}

	param_float[paramKey] = value;
}

void AnimationController::SetBool(std::string paramKey, bool value)
{
	if (param_bool.find(paramKey) == param_bool.end()) {
		std::cout << "[ ERROR ] Nonexistent animation parameter identifier (bool)" << std::endl;
		return;
	}

	param_bool[paramKey] = value;
}

void AnimationController::SetTrigger(std::string paramKey)
{
	if (param_trigger.find(paramKey) == param_trigger.end()) {
		std::cout << "[ ERROR ] Nonexistent animation parameter identifier (trigger)" << std::endl;
		return;
	}

	param_trigger[paramKey] = true;
}

int AnimationController::GetParameterInt(std::string paramKey)
{
	if (param_int.find(paramKey) == param_int.end()) {
		std::cout << "[ ERROR ] Nonexistent animation parameter identifier (int)" << std::endl;
		return 0;
	}

	return param_int[paramKey];
}

float AnimationController::GetParameterFloat(std::string paramKey)
{
	if (param_float.find(paramKey) == param_float.end()) {
		std::cout << "[ ERROR ] Nonexistent animation parameter identifier (float)" << std::endl;
		return 0.0f;
	}

	return param_float[paramKey] ;
}

bool AnimationController::GetParameterBool(std::string paramKey)
{
	if (param_bool.find(paramKey) == param_bool.end()) {
		std::cout << "[ ERROR ] Nonexistent animation parameter identifier (bool)" << std::endl;
		return false;
	}

	return param_bool[paramKey];
}
