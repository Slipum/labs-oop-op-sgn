#ifndef OOP4_OPERATIONS_H
#define OOP4_OPERATIONS_H

#include <string>
#include "../scene/scene.h"

class FacadeOperationResult {
public:
    FacadeOperationResult(std::string errorMessage,
    bool isSuccess) : _errorMessage(errorMessage), _isSuccess(isSuccess) {};

    std::string GetErrorMessage() { return _errorMessage; };
    bool IsSuccess() { return _isSuccess; };
private:
    std::string _errorMessage;
    bool _isSuccess;
};

struct NormalizationParameters {
    float Min;
    float Max;
    float DxStep;
    float DyStep;
};

class BaseFileReader {
public:
    virtual ~BaseFileReader() = default;

    virtual Scene&& ReadScene(std::string path, NormalizationParameters parameters) = 0;
};

class FileReader : public BaseFileReader {
public:
    Scene&& ReadScene(std::string path, NormalizationParameters parameters) override;
};

#endif //OOP4_OPERATIONS_H
