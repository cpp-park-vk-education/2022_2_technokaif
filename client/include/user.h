#ifndef _USER_H_
#define _USER_H_

#include "tools/utils.h"

class IUser {
 public:
    virtual void setId(int) = 0;
    virtual void setName(std::string) = 0;
    virtual void setEmail(std::string) = 0;
    virtual void setPasswordHash(std::string) = 0;
    virtual void setUrlList(std::vector<std::string>) = 0;

    virtual int getId() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getEmail() const = 0;
    virtual std::string getPasswordHash() const = 0;
    virtual std::vector<std::string> getUrlList() const = 0;
};

class User : public IUser {
 public:
    void setId(int) override;
    int getId() const override;

    void setName(std::string) override;
    std::string getName() const override;

    void setEmail(std::string) override;
    std::string getEmail() const override;

    void setPasswordHash(std::string) override;
    std::string getPasswordHash() const override;

    void setUrlList(std::vector<std::string>) override;
    std::vector<std::string> getUrlList() const override;

 private:
    int Id;
    std::string name;
    std::string password;
    std::string email;
};

#endif  // _USER_H_
