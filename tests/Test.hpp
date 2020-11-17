//
//  Test.hpp
//  OpenGl
//
//  Created by Ihor Prytula on 21.09.2020.
//  Copyright © 2020 Ihor Prytula. All rights reserved.
//

#ifndef Test_hpp
#define Test_hpp

#include <stdio.h>

namespace test {

class Test {
protected:
    bool m_enable = false;
public:
    Test(){};
    virtual ~Test(){};
    
    bool isEnable() const {
        return m_enable;
    }
    void EnableTest() {
        m_enable = true;
    }
    void DisableTest() {
        m_enable = false;
    }
    
    virtual const char* getTestName() = 0;
    virtual void OnUpdate(float deltaTime){}
    virtual void OnRender(){}
    virtual void OnImGuiRender() = 0;
};

}

#endif /* Test_hpp */
