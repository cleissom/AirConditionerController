//
// Created by cleissom on 4/28/21.
//

#include <jni.h>
#include "../../../../../List.hpp"


typedef struct
{
    uint8_t id;
    char datetime[20];
    char message[20];
} log_t;

List<log_t> list;

stringstream &operator<<(stringstream &s, const log_t &log)
{
    s << "id: " << unsigned(log.id) << ", datetime:" << log.datetime << ", message:" << log.message;
    return s;
}

extern "C" JNIEXPORT jstring JNICALL Java_com_example_hospedeiro_1smartphone_MainActivity_getMessage(JNIEnv *env, jobject thisObj) {


    return env->NewStringUTF("Hello from native code!");
};

uint8_t testid = 0;

extern "C" JNIEXPORT void JNICALL Java_com_example_hospedeiro_1smartphone_MainActivity_loadData(JNIEnv *env, jobject thisObj) {
    // Aqui deverá ser chamado uma função que obtém os dados do sistema através do Bluetooth e após isso deverá ser inserido na lista

    list.insertAfterLast({
             .id = testid++,
             .datetime = "2021/04/28-15:33:28",
             .message = "start"
     });
};

extern "C" JNIEXPORT jstring JNICALL Java_com_example_hospedeiro_1smartphone_MainActivity_listData(JNIEnv *env, jobject thisObj) {
    stringstream s;
    list.listAll(s);
    return env->NewStringUTF(s.str().c_str());
};