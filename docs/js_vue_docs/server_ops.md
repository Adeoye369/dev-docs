# Server Operations

## Recommended Status Codes

**401 Unauthorized:** This is the primary code for authentication failure. It indicates that the request lacks valid credentials for the target resource.

**403 Forbidden:** Used when the user is successfully authenticated but lacks the necessary permissions to access a specific resource (e.g., a standard user trying to access an admin panel). It is also sometimes used for accounts that are suspended or blocked.

**400 Bad Request:** Appropriate for malformed login requests, such as missing required fields (e.g., an empty password field) or invalid syntax in the request body.

**422 Unprocessable Entity:** Frequently used in modern APIs to indicate semantic errors, such as a password that does not meet security requirements or an email format that is valid but not found in the system.

**429 Too Many Requests:** Used for rate-limiting after multiple failed login attempts to prevent brute-force attacks.

## Runing Json server

1. Install `json-server` using `npm i json-server`
2. Rename your `jobs.json` to be in this format

    ```json
          {
            "jobs":[
              {...job1 details},
              {...job2 details},
              ...
            ]
          }
    ```

3. In your *package.json* file, at the script section add `server`

    ```json hl_lines="11"
            {
              "name": "vue001_introduction",
              "version": "0.0.0",
              "private": true,
              "type": "module",
              "scripts": {
                "dev": "vite",
                "build": "vite build",
                "preview": "vite preview",
                "server1": "json-server --watch src/jobs.json --port 1234"
              },
                ...
            }
    ```

4. Create new terminal in vscode `ALT + CTRL + (~)`
then run `npm run server1` server1 being the name you decide.

5. Install Axios `npm i axios`  that will be used to run CRUD operation
6. In the *JobListings.vue* do the following

    ```html title="JobListings.vue" hl_lines="2 3 7-9 18-26 36"
    <script setup>
    import {ref, reactive, onMounted} from 'vue' // add onMounted
    import axios from 'axios'                   // Add axios
    import JobListing from '@/components/JobListing.vue'

    // Change ref to reactive
    const state = reactive({ 
        jobs: [],
        isLoading: true
    })

    defineProps({
        limit: Number,
        showAllJobs: {type: Boolean, default: false}
    })

    // Loading jobs from Json server
    onMounted(async () =>{
        try {
            const response = await axios.get("http://localhost:1234/jobs")
            state.jobs = response.data
        } catch (error) {
            console.error("Error fetching jobs : ",  error)
        } finally{
            state.isLoading = false;
        }
    })

    </script>

    <template>
        ...
                <div class="grid grid-cols-1 md:grid-cols-3 gap-6">
                    <!-- Display on limit amount -->
                    <JobListing 
                    v-for="job in state.jobs.slice(0, limit || state.jobs.length)" 
                    :job-data="job" />
                </div>
            </div>
        </section>

       ...
    </template>
    ```

## Replacing LocalHost with '/api'

```js title="vite.config.js" hl_lines="6-14"
export default defineConfig({
  plugins: [
    vue(),
    ...
  ],
  server:{
    proxy: {
      '/api' : {
        target:'http://localhost:1234',
        changeOrigin: true,
        rewrite: (path)=>path.replace(/^\/api/, '')
      }
    }
  },
  resolve: {
    ...
  },
})

```