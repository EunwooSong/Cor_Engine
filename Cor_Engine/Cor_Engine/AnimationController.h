#pragma once
#include "Component.h"
#include "SpriteAnimation.h"
#include <any>
#include <string>

enum AnimOper {
    GREATER,
    LESS,
    EQUALS,
    N_EQUALS,
    TRIGGER
};

using trigger = bool;


template <typename T>
struct StateNode {
    std::string paramName;

    bool isHasExitTime;
    T targetValue;
    AnimOper operater;

    std::string changeNodeName;
};

struct AnimationNode {
    SpriteAnimation* currentAnim;

    std::vector<StateNode<int>>   stateType_int;
    std::vector<StateNode<float>> stateType_float;
    std::vector<StateNode<bool>>  stateType_bool;
};

class AnimationController :
    public Component
{
public:
    AnimationController();
    ~AnimationController();

    void Start() override;
    void Update() override;
    void Render() override;
    void EndScene() override;

    void CheckAnimationState();
    SpriteAnimation* GetCurrentAniamtion();

    template<typename T>
    void AddParameter(std::string paramKey);

    template<typename T>
    void AddParameter(std::string paramKey, T value);

    void AddAnimationNode(std::string nodeName, SpriteAnimation* p_anim);

    template<typename T>
    void AddState(std::string targetAnim, std::string paramName, AnimOper oper, T value, std::string nextAnim, bool isHasExitTime = true);

    void AddTrigger(std::string paramKey, std::string targetAnim);

    void SetEntryAnimationNode(std::string targetAnim);
    
    void SetInt(std::string paramKey, int value);
    void SetFloat(std::string paramKey, float value);
    void SetBool(std::string paramKey, bool value);
    void SetTrigger(std::string paramKey);

    int   GetParameterInt         (std::string paramKey);
    float GetParameterFloat       (std::string paramKey);
    bool  GetParameterBool        (std::string paramKey);

private:
    std::map<std::string, AnimationNode*>::iterator     entry_node;
    std::map<std::string, AnimationNode*>::iterator     current_node;
    std::map<std::string, AnimationNode*>               anim_node;
    std::vector<StateNode<trigger>>                     stateType_Trigger;
    
    std::map<std::string, int>      param_int;
    std::map<std::string, float>    param_float;
    std::map<std::string, bool>     param_bool;
    std::map<std::string, trigger>  param_trigger;
};  

template<typename T>
inline void AnimationController::AddParameter(std::string paramKey)
{
    switch (typeid(T).name)
    {
    case "int"      : param_int.insert(std::pair<std::string, int>(paramKey, (int)0));                  break;
    case "float"    : param_float.insert(std::pair<std::string, float>(paramKey, (float).0f));          break;
    case "bool"     : param_bool.insert(std::pair<std::string, bool>(paramKey, (bool)false));           break;
    case "trigger"  : param_trigger.insert(std::pair<std::string, trigger>(paramKey, (trigger)false )); break;
    default: std::cout << "[ ERROR ] Animation Parameter Type Error " << std::endl;                     break;
    }
}

template<typename T>
inline void AnimationController::AddParameter(std::string paramKey, T value)
{
    switch (typeid(T).name)
    {
    case "int"      : param_int.insert(std::pair<std::string, int>(paramKey, (int)value));              break;
    case "float"    : param_float.insert(std::pair<std::string, float>(paramKey, (float)value));        break;
    case "bool"     : param_bool.insert(std::pair<std::string, bool>(paramKey, (bool)value));           break;
    case "trigger"  : param_trigger.insert(std::pair<std::string, trigger>(paramKey, (trigger)value));  break;
    default: std::cout << "[ ERROR ] Animation Parameter Type Error " << std::endl;                     break;
    }
}

template<typename T>
inline void AnimationController::AddState(std::string targetAnim, std::string paramName, AnimOper oper, T value, std::string nextAnim, bool isHasExitTime)
{
    bool isError = false;
    if (anim_node[targetAnim] == anim_node.end() || anim_node[nextAnim] == anim_node.end()) {
        std::cout << "[ ERROR ] Animation name is error, check parameter targetAnim or nextAnim" << std::endl;
        return;
    }

    if (strcmp(typeid(T).name(), "trigger")) {
        std::cout << "[ ERROR ] The type passed is the trigger. Automatically adding to stateType_trigger..." << std::endl;
        AddTrigger(paramKey, targetAnim);
        return;
    }

    AnimationNode* iter = anim_node[targetAnim];
    
    StateNode<T> state;
    state.paramName = paramName;
    state.isHasExitTime = isHasExitTime;
    state.operater = oper;
    state.targetValue = value;
    state.changeNodeName = nextAnim;

    switch (typeid(T).name())
    {
    case "int":     iter->stateType_int.push_back(state);   break;
    case "float":   iter->stateType_float.push_back(state); break;
    case "bool":    iter->stateType_bool.push_back(state);  break;
    default:        std::cout << "[ ERROR ] Animation State Type Error" << std::endl;  break;
    }
}