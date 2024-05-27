/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ErrorAI.hpp
*/

#pragma once
#include <exception>
#include <iostream>

namespace Zappy {

    enum ErrorType {
        SocketError,
        ArgError
    };

    class ErrorAI : public std::exception {
        public:
            ErrorAI(const std::string &msg);
            ErrorAI(ErrorType error);
            ErrorAI(ErrorType error, const std::string &msg);
            virtual ~ErrorAI() = default;

            const char* what() const noexcept override;

        private:
            mutable std::string _msg;
    };
}
