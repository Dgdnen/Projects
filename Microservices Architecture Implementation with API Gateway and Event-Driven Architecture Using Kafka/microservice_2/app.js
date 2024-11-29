const express = require('express');
const { Kafka } = require('kafkajs');
const grpc = require('@grpc/grpc-js');
const protoLoader = require('@grpc/proto-loader');
const packageDefinition = protoLoader.loadSync('messages.proto');
const messages_proto = grpc.loadPackageDefinition(packageDefinition).messages;

const microserviceId = 'ms2';
const port = 3002;
const grpc_port = 50051;
const kafkaURL = 'localhost:9092'
const kafkaTopic = "kafka_topic";
const kafkaGroup = "group_" + microserviceId;

// DATABASE
const data_base_client = {
	Elon_Musk: ['$USD 10,000,000', 'CEO']
}

// Create Kafka
const kafka = new Kafka({
  clientId: microserviceId,
  brokers: [ kafkaURL ]
});

// Kafka producer + consumer
const producer = kafka.producer();
const consumer = kafka.consumer({ groupId: kafkaGroup });
var check_received = false;
var received_message = "";

// Connect Kafka
const connectKafka = async () => {
  await producer.connect();
  await consumer.connect();
  await consumer.subscribe({ topic: kafkaTopic });
  
  await consumer.run({
    eachMessage: async ({ topic, partition, message }) => {
      const parsedMessage = JSON.parse(message.value.toString());
      // Check if message was not sent by the same agent
      if (parsedMessage.microserviceId !== microserviceId) {
        console.log(`Got message from ${parsedMessage.microserviceId}: ${parsedMessage.message}`);
		check_received = true;
		received_message = parsedMessage.message;
      }
    },
  });
};
connectKafka().catch(console.error);

const sendMessageKafka = async (data) => {
	console.log(`Sending data through kafka: ${data}`);
	await producer.send({
		topic: kafkaTopic,
        messages: [{ value: JSON.stringify({ microserviceId, message: data }) }]
    });
};

const waitForKafkaMessage = async () => {
	console.log(`Waiting for kafka to send data..`);
	while (!check_received) {
		// Wait for a short duration to avoid blocking the event loop
		await new Promise(resolve => setTimeout(resolve, 100));
	}
	return received_message;
};

// Create an express app
const app = express();

// Add middleware
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

// Setup Grpc Client
const client = new messages_proto.Messenger(`localhost:${grpc_port}`, grpc.credentials.createInsecure());  

app.post("/", (req, res) => {
	console.log(req.body);
	
	const name = req.body.name;
	var value = "";
	var number = "";
	
	client.SendMessage({
            from: microserviceId,
            content: name
        },
            async (err, response) => {
                if (err) {
                    console.log('Error sending message: ', err);
					value = "error";
                }
                else {
                    console.log(`Got the following response: ${response.content}`);
					value = response.content;
                }
				
				if (value == "not_found" || value == "error") {
					res.json({ ok: false });
				}
				else {
					// Wait for kafka
					check_received = false;
					number = await waitForKafkaMessage();
					
					res.json({ ok: true, valoare: value, nr: number });
				};
        });
});

app.post("/client-info", (req, res) => {
	console.log(`POST on "/client-info" with ${req.body}`);
	
	const client_name = req.body.name;
	
	if (client_name in data_base_client) {
		console.log(`data_to_send = ${data_base_client[client_name][0]}`);
		res.json({ value: data_base_client[client_name][0] });
		console.log(`Data sent.`);
		
		// Initiate kafka message to send
		sendMessageKafka(data_base_client[client_name][1]);
	}
	else {
		console.log(`${client_name} not found`);
		res.json({ value: "not_found" });
	}
});

app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});
