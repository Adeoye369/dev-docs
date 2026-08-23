# Slot in Vue

In Vue, a slot is a template placeholder that allows a parent component to pass dynamic HTML markup, text, or other components into a child component. It serves as a visual "hole" or entry point, letting you create highly flexible, reusable components where the child manages layout and behavior, while the parent determines the specific UI content.

## 1. Default Slots
The simplest implementation is an unnamed slot. Anything wrapped inside the child component tags by the parent gets injected straight into the `<slot/>` tag location.

*Child Component `(MyButton.vue)`*
```vue  title="(MyButton.vue)"
<template>
  <button class="btn-primary">
    <!-- Content from the parent goes here -->
    <slot>Default Button Text</slot> 
  </button>
</template>

```
!!!Note: The text "Default Button Text" acts as fallback content if the parent passes nothing.


*Parent Component `(App.vue)`*
```vue title="App.vue"
<template>
  <!-- Overrides default text -->
  <MyButton>Click Me!</MyButton>
  
  <!-- Uses fallback text -->
  <MyButton /> 
</template>

```

## 2. Named Slots

When your child component requires multiple placement areas (like a modal layout with a header, body, and footer), you assign a name attribute to individual slots. The parent directs content to these spots using the `v-slot` directive or its `#` shorthand

```vue title="BaseCard.vue"
<template>
  <div class="card">
    <header>
        <slot name="header"></slot>
    </header>
    
    <main>
        <!-- Implicitly named "default" -->
        <slot><slot /> 
    </main>
 
    <footer>
        <slot name="footer"></slot>
    </footer>
  </div>
</template>

```

```vue title="App.vue"
<template>
  <BaseCard>
    <!-- Targeting the header slot -->
    <template #header>
      <h3>Special Alert</h3>
    </template>

    <!-- Implicitly targets the default slot -->
    <p>This is the main structural body text.</p>

    <!-- Targeting the footer slot using full directive syntax -->
    <template v-slot:footer>
      <button>Close</button>
    </template>
  </BaseCard>
</template>
```

## 3. Conditional Slots

A conditional slot uses Vue's `v-if` directive coupled with the global $slots object to check if the parent component actually passed down content. This prevents empty HTML wrapper elements from rendering and breaking your layout grid, margins, or padding.

*Child Component `(CardModal.vue)`*

```vue title="CardModal.vue"
<template>
  <div class="modal">
    <!-- Only render the header container if the parent provided content for it -->
    <header v-if="$slots.header" class="modal-header">
      <slot name="header" />
    </header>

    <main class="modal-body">
      <slot />
    </main>

    <!-- Only render the footer container if the parent provided content for it -->
    <footer v-if="$slots.footer" class="modal-footer">
      <slot name="footer" />
    </footer>
  </div>
</template>

```

*Parent Component `(App.vue)`*

```vue
<template>
  <!-- Example 1: Header and footer are rendered because slots are populated -->
  <CardModal>
    <template #header>
        <h1>System Alert</h1>
    </template>

    <p>Operation completed successfully.</p>

    <template #footer>
        <button>Dismiss</button>
    </template>
  </CardModal>

  <!-- Example 2: The <header> and <footer> tags will not render at all in the DOM -->
  <CardModal>
    <p>Just simple text without structural wrappers.</p>
  </CardModal>
</template>
```

## 4. Scoped Slots (Passing Data Upward)

By default, slot content only has access to the parent component's data scope. However, if the parent needs access to internal state or data computed inside the child component, you can bind data properties as attributes directly onto the child's `<slot>` tag

A scoped slot acts like a function inside the child component that accepts arguments (props) and passes them back out to the parent layout. This is highly useful for abstracting logic (like data fetching, filtering, or list rendering) while keeping the visual layout entirely customizable by the parent.

### Example 1

*Child Component `(UserList.vue)`*

```vue
<script setup>
const user = { name: 'Alex', role: 'Admin' }
</script>

<template>
  <div class="user-container">
    <!-- Passing the local object data up via custom slot props -->
    <slot :userData="user" />
  </div>
</template>

```

*Parent Component `(App.vue)`*

```vue
<template>
  <UserList v-slot="slotProps">
    <!-- Accessing child data directly in parent markup -->
    <p>User name is: {{ slotProps.userData.name }}</p>
    <span>Role: {{ slotProps.userData.role }}</span>
  </UserList>
</template>
```

### Example 2

*Child Component `(DataTable.vue)`*
```vue
<script setup>
// Mock data inside the child component
const activeUsers = [
  { id: 1, name: 'Sarah', status: 'active', points: 1200 },
  { id: 2, name: 'Michael', status: 'suspended', points: 450 }
]
</script>

<template>
  <table>
    <thead>
      <tr><th>Name</th><th>Status</th></tr>
    </thead>
    <tbody>
      <tr v-for="user in activeUsers" :key="user.id">
        <td>{{ user.name }}</td>
        <td>
          <!-- Bind 'user' as a custom prop named 'row' to pass it back up -->
          <slot name="statusColumn" :row="user">
            <!-- Default fallback text if parent doesn't override -->
            {{ user.status }}
          </slot>
        </td>
      </tr>
    </tbody>
  </table>
</template>

```
*Parent Component `(App.vue)`*

```vue
<template>
  <DataTable>
    <!-- Use destructuring ({ row }) to read variables emitted by the child -->
    <template #statusColumn="{ row }">
      <span :class="row.status === 'active' ? 'badge-green' : 'badge-red'">
        {{ row.status.toUpperCase() }} ({{ row.points }} pts)
      </span>
    </template>
  </DataTable>
</template>

```





