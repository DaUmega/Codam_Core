<template>
  <div id="app">
    <div class="background"></div>
    <Header />
    <div class="content-container">
      <router-view></router-view>
    </div>
  </div>
</template>

<script>
import CustomButton from './components/general/CustomButton.vue'
import Header from './components/general/AppHeader.vue'

export default {
  name: 'App',
  components: {
    Header
  }
}
</script>

<style lang="scss">
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
}

.background {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-image: url('./images/backround.jpeg');
  background-size: cover;
  background-position: center;
  z-index: -1;
}

.content-container {
  margin-top: 2rem; /* Add top margin for the content */
}
</style>
