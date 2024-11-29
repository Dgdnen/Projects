const express = require('express');
const { Kafka } = require('kafkajs');
const grpc = require('@grpc/grpc-js');
const protoLoader = require('@grpc/proto-loader');
const packageDefinition = protoLoader.loadSync('messages.proto');
const messages_proto = grpc.loadPackageDefinition(packageDefinition).messages;

const microserviceId = 'ms1';
const port = 3001;
const client_ms_url = "http://localhost:3002/client-info";
const grpc_port = 50051;
const kafkaURL = 'localhost:9092'
const kafkaTopic = "kafka_topic";
const kafkaGroup = "group_" + microserviceId;

// DATABASE
const data_base_company = {
	Tesla: ['$USD 70,000,000', '25,000'],
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

app.post("/", (req, res) => {
	console.log(`POST on "/" with ${req.body}`);
	
	const name = req.body.name;
	var value = "";
	var position = "";

// CASE: CLIENT

	const fetchClient = async (cl_name) => {
		console.log("Fetch Client");
        const response = await fetch(client_ms_url, {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json'
			},
			body: JSON.stringify({ name: cl_name })
		});
        const data = await response.json();
		
		return data.value;
    };

// CASE: COMPANY
	
	fetchClient(name).then(async val => {
		console.log(`Got value for client: ${val}`);
		value = val;
		
		if (value == "not_found") {
			console.log(`Client not found`);
			res.json({ ok: false });
		}
		else {
			// Wait for kafka
			check_received = false;
			position = await waitForKafkaMessage();
			
			const data_to_send = { ok: true, avere: value, functie: position };
			console.log(`Sending data: ${data_to_send}`);
			res.json(data_to_send);
		};
	});
});

app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});

// Setup Grpc Server
const server = new grpc.Server();

function SendMessage(call, callback) {
    console.log(`Received message from ${call.request.from}: ${call.request.content}`);
	const company_name = call.request.content.toString();
	
	if (company_name in data_base_company) {
		console.log(`data_to_send = ${data_base_company[company_name][0]}`);
		callback(null, { from: microserviceId, content: data_base_company[company_name][0] });
		
		// Initiate kafka message to send
		sendMessageKafka(data_base_company[company_name][1]);
	}
	else {
		console.log(`${company_name} not found`);
		callback(null, { from: microserviceId, content: "not_found" });
	}
}

server.addService(messages_proto.Messenger.service, { SendMessage });
server.bindAsync(`localhost:${grpc_port}`, grpc.ServerCredentials.createInsecure(),
	(err, port) => {
		if (err) {
			console.error('Error starting server: ', err);
		}
		else {
			console.log(`Server started on port ${port}`);
		}
	}
);
