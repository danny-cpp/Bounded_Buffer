#pragma once

#include "PCH.h"
#include "iomanip"


namespace ProdCon {
    class IOManagement {
    public:

        explicit IOManagement(std::string &file_name) {
            reset_point = std::cout.rdbuf();
            std::cout.rdbuf(target_file.rdbuf());
            target_file = std::ofstream(file_name);
        }

        void bind() {
            reset_point = std::cout.rdbuf();
            std::cout.rdbuf(target_file.rdbuf());
        }

        void release() {
            std::cout.rdbuf(reset_point);
        }

        static void write_list(double time_stamp, int ID, int Q_number, std::string &status, int N_number) {
            std::cout << std::left << std::setw(6) << std::setfill(' ') << time_stamp;
            std::cout << "ID= ";
            std::cout << std::right << std::setw(2) << std::setfill(' ') << ID;
            if (Q_number != -1) {
                std::cout << " Q= ";
                std::cout << std::right << std::setw(3) << std::setfill(' ') << Q_number;
            }
            else {
                std::cout << "    ";
                std::cout << std::right << std::setw(3) << std::setfill(' ') << ' ';
            }
            std::cout << " ";
            std::cout << std::left << std::setw(11) << std::setfill(' ') << status;
            if (N_number != -1) {
                std::cout << std::right << std::setw(3) << std::setfill(' ') << N_number;
            }
            else {
                std::cout << std::right << std::setw(3) << std::setfill(' ') << ' ';
            }
            std::cout << std::endl;
        }

    private:
        std::ofstream target_file;
        std::streambuf *reset_point;
    };

}
