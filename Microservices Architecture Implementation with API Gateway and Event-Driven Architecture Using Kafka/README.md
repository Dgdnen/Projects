# Microservices Architecture with API Gateway and Event-Driven Architecture Using Kafka

## Project Overview
This project involves the design and implementation of a hybrid microservices architecture that integrates an **API Gateway** and **event-driven communication** via **Kafka**. The system is containerized using **Docker** and employs various modern technologies including **Express.js**, **Kafka**, **gRPC**, **Tailwind CSS**, **Node.js**, and **HTML** to provide a scalable, efficient, and maintainable architecture. The project is associated with **Universitatea Transilvania din Brașov** and spans from **April 2024 to May 2024**.

## Objectives
The main goal of this project is to demonstrate the utility of various software architecture concepts, including:
- **Microservices Architecture**: Dividing the system into small, independent services.
- **API Gateway**: A central point to route requests and manage services.
- **Event-Driven Architecture**: Using Kafka for asynchronous communication between microservices.
- **Containerization**: Deploying the entire system in Docker containers for portability and scalability.

## Technologies Used
- **Express.js**: For building RESTful APIs within microservices.
- **Kafka**: For event-driven communication between microservices, enabling decoupling.
- **Tailwind CSS**: For frontend styling with a utility-first CSS framework.
- **Docker**: For containerizing microservices and other components.
- **gRPC**: For efficient communication between microservices, especially for low-latency, high-performance operations.
- **Node.js**: Backend development environment using a non-blocking, event-driven model.
- **HTML**: For building the frontend interface.

## Architecture Overview
The architecture is designed as a hybrid of **API Gateway** and **Event-Driven** communication, leveraging **Kafka** for messaging between microservices. The components are as follows:
- **Frontend**: Built using HTML and styled with Tailwind CSS.
- **API Gateway**: Handles incoming requests and routes them to the appropriate microservices.
- **Microservices 1 and 2**: Two microservices that handle different logic and communicate with each other using REST, gRPC, and Kafka.
- **Kafka**: A message broker for event-driven communication between microservices.
- **Docker**: All components are containerized for portability and ease of deployment.

## Implementation Details

### User Flow
1. **Homepage**: The user can input a name (client or company) and choose the type of information to retrieve (client or company).
2. **API Gateway**: Routes the request to the appropriate microservice.
3. **Microservices**: 
   - Microservice 1 and Microservice 2 interact through **REST** and **gRPC** protocols.
   - Kafka is used for asynchronous event-driven communication.
4. **Response**: After processing, the data is returned to the user in the frontend.

### Scenarios
- **Scenario 1**: The user enters a valid client name and receives client-specific information.
- **Scenario 2**: The user enters a valid company name and receives company-specific information.
- **Scenario 3**: If no results are found, the system will return a message stating that no results were found in the database.

## Project Components
### 1. **Frontend (HTML + Tailwind CSS)**
- The frontend interface allows users to enter data and display the information retrieved by the backend services.

### 2. **API Gateway**
- The API Gateway serves as the entry point for all incoming requests and forwards them to the appropriate microservice.

### 3. **Microservices**
- **Microservice 1**: Handles client-specific information retrieval.
- **Microservice 2**: Handles company-specific information retrieval.

### 4. **Kafka**
- Kafka is used for event-driven communication between microservices, enabling decoupled interactions and scaling.

### 5. **Docker**
- All components (frontend, API Gateway, microservices, Kafka) are containerized using Docker for ease of deployment.
