#pragma once
#include "Component.h"
#include "SpriteAnimation.h"
#include <any>
#include <string>

enum AnimOper {
    GREATER,
    LESS,
    EQUALS,
    N_EQUALS
};

using trigger = bool;


template <typename T>
struct StateNode {
    std::string paramName;
    AnimOper operater;
    T targetValue;

    bool CheckOperater(T paramValue) {
        switch (operater)
        {
        case GREATER:
            return paramValue > targetValue;    break;
        case LESS:
            return paramValue < targetValue;    break;
        case EQUALS:
            return paramValue == targetValue;   break;
        case N_EQUALS:
            return paramValue != targetValue;   break;
        default:
            return false;
            break;
        }
    }
};

struct StateGroup {
    bool isHasExitTime;

    std::vector<StateNode<int>>   stateType_int;
    std::vector<StateNode<float>> stateType_float;
    std::vector<StateNode<bool>>  stateType_bool;
};

struct AnimationNode {
    SpriteAnimation* currentAnim;

    std::map<std::string, StateGroup*> stateGroup;
};

class AnimationController :
    public Component
{
public:
    AnimationController();
    ~AnimationController();

    //Animation 생성 순서
    //1. SpriteAnimation을 생성한다
    //2. Parameter을 설정한다.
    //3. AnimationNode를 추가한다.
    //4. AddState를 통해 state를 등록한다.
    //5. SetEntryAniamtionNode을 통해 시작 Animation을 설정한다

    void Start() override;
    void Update() override;
    void LateUpdate() override;
    void Render() override;

    void CheckAnimationState();
    SpriteAnimation* GetCurrentAniamtion();

    template<typename T>
    void AddParameter(std::string paramKey);

    template<typename T>
    void AddParameter(std::string paramKey, T value);

    void AddAnimationNode(std::string nodeName, SpriteAnimation* p_anim);

    void SetHasExitTime(std::string targetNode, std::string nextNode, bool isHasExitTime);
    template<typename T>
    void AddState(std::string targetAnim, std::string paramName, AnimOper oper, T value, std::string nextAnim);

    void AddTrigger(std::string paramKey, std::string targetAnim);

    void SetEntryAnimationNode(std::string targetAnim);
    
    void SetInt     (std::string paramKey, int      value);
    void SetFloat   (std::string paramKey, float    value);
    void SetBool    (std::string paramKey, bool     value);
    void SetTrigger (std::string paramKey);

    int   GetParameterInt         (std::string paramKey);
    float GetParameterFloat       (std::string paramKey);
    bool  GetParameterBool        (std::string paramKey);

private:
    void ChangeAnimationNode(std::string nextAnim);

    std::map<std::string, AnimationNode*>::iterator     entry_node;
    std::map<std::string, AnimationNode*>::iterator     current_node;
    std::map<std::string, AnimationNode*>               anim_node;
    std::map<std::string, StateNode<trigger>>           stateType_Trigger;
    
    std::map<std::string, int>      param_int;
    std::map<std::string, float>    param_float;
    std::map<std::string, bool>     param_bool;
    std::map<std::string, trigger>  param_trigger;
};  

template<typename T>
inline void AnimationController::AddParameter(std::string paramKey)
{
    const char* tmpName = typeid(T).name();

    if(strcmp("int", tmpName) == 0)
        param_int.insert(std::pair<std::string, int>(paramKey, (int)0));
    else if(strcmp("float", tmpName) == 0)
        param_float.insert(std::pair<std::string, float>(paramKey, (float).0f));
    else if(strcmp("bool", tmpName) == 0)
        param_bool.insert(std::pair<std::string, bool>(paramKey, (bool)false));
    else if(strcmp("trigger", tmpName) == 0)
        param_trigger.insert(std::pair<std::string, trigger>(paramKey, (trigger)false));
    else
        std::cout << "[ ERROR ] Animation Parameter Type Error " << std::endl;
}

template<typename T>
inline void AnimationController::AddParameter(std::string paramKey, T value)
{
    const char* tmpName = typeid(T).name();

    if (strcmp("int", tmpName) == 0)
        param_int.insert(std::pair<std::string, int>(paramKey, (int)value));
    else if (strcmp("float", tmpName) == 0)
        param_float.insert(std::pair<std::string, float>(paramKey, (float)value));
    else if (strcmp("bool", tmpName) == 0)
        param_bool.insert(std::pair<std::string, bool>(paramKey, (bool)value));
    else if (strcmp("trigger", tmpName) == 0)
        param_trigger.insert(std::pair<std::string, trigger>(paramKey, (trigger)value));
    else
        std::cout << "[ ERROR ] Animation Parameter Type Error " << std::endl;
}

template<typename T>
inline void AnimationController::AddState(std::string targetAnim, std::string paramName, AnimOper oper, T value, std::string nextAnim)
{
    bool isError = false;
    if (anim_node.find(targetAnim) == anim_node.end() || anim_node.find(nextAnim) == anim_node.end()) {
        std::cout << "[ ERROR ] Nonexistent Animation identifier " << std::endl;
        return;
    }

    AnimationNode* iter = anim_node[targetAnim];
    
    const char* tmpName = typeid(T).name();

    if (iter->stateGroup.find(nextAnim) == iter->stateGroup.end())
        SetHasExitTime(targetAnim, nextAnim, true);

    if (strcmp("int", tmpName) == 0) {
        StateNode<int> state;
        state.paramName = paramName;
        state.operater = oper;
        state.targetValue = value;
        iter->stateGroup[nextAnim]->stateType_int.push_back(state);
    }
    else if (strcmp("float", tmpName) == 0) {
        StateNode<float> state;
        state.paramName = paramName;
        state.operater = oper;
        state.targetValue = value;
        iter->stateGroup[nextAnim]->stateType_float.push_back(state);
    }
    else if (strcmp("bool", tmpName) == 0) {
        StateNode<bool> state;
        state.paramName = paramName;
        state.operater = oper;
        state.targetValue = value;
        iter->stateGroup[nextAnim]->stateType_bool.push_back(state);
    }
    else
        std::cout << "[ ERROR ] Animation State Type Error" << std::endl;
}