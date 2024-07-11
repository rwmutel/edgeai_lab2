#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

const int MATRIX_SIZE = 2048;

void generate_matrix(std::vector<std::vector<float>>& matrix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = static_cast<float>(dis(gen));
        }
    }
}

void multiply_matrices(const std::vector<std::vector<float>> &A,
                    const std::vector<std::vector<float>> &B,
                       std::vector<std::vector<float>> &C,
                       int start_row, int end_row) {
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    std::vector<std::vector<float>> A(MATRIX_SIZE, std::vector<float>(MATRIX_SIZE));
    std::vector<std::vector<float>> B(MATRIX_SIZE, std::vector<float>(MATRIX_SIZE));
    std::vector<std::vector<float>> C(MATRIX_SIZE, std::vector<float>(MATRIX_SIZE));

    generate_matrix(A);
    generate_matrix(B);

    auto start = std::chrono::high_resolution_clock::now();

    // int num_threads = std::thread::hardware_concurrency();
    int num_threads = 4;
    std::vector<std::thread> threads(num_threads);

    int rows_per_thread = MATRIX_SIZE / num_threads;
    for (int t = 0; t < num_threads; ++t) {
        int start_row = t * rows_per_thread;
        int end_row = (t + 1) * rows_per_thread;
        threads[t] = std::thread(multiply_matrices, std::cref(A), std::cref(B), std::ref(C), start_row, end_row);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken for matrix multiplication: " << duration.count() << " seconds" << std::endl;

    return 0;
}
