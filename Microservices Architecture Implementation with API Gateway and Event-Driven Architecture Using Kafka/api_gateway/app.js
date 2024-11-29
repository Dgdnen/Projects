const express = require('express');

const port = 3000;
const microservice_1_url = "http://localhost:3001/";
const microservice_2_url = "http://localhost:3002/";

// Create an express app
const app = express();

// Add middleware
app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.post("/", (req, res) => {
    console.log(req.body);

    const req_type = req.body.type_name; // client or company
    const req_val = req.body.val_name.replace(" ", "_"); // name of client or company

// CASE: CLIENT

    const fetchClient = async (cl_name) => {
        const response = await fetch(microservice_1_url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ name: cl_name })
        });
        const data = await response.json();
		// console.log(`Received ${data} from microservice 1`);
		console.log(`Sending ${data} to client`);
        return data;
    };


// CASE: COMPANY

    const fetchCompany = async (co_name) => {
        const response = await fetch(microservice_2_url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ name: co_name })
        });
        const data = await response.json();
		console.log(`Sending ${data} to client`);
        return data;
    };

    if (req_type === "cl") {
        fetchClient(req_val).then(cl_data => {
            res.json(cl_data);
        });
    } else if (req_type === "co") {
        fetchCompany(req_val).then(co_data => {
            res.json(co_data);
        });
    }
});

app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});
