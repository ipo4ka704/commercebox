<?php

/**
 * @file
 * Admin page callback file for the ui_elements module.
 */


/**
 * Form constructor for the background style settings.
 *
 * @see ui_elements_bg_form_submit()
 * @ingroup forms
 */
function ui_elements_bg_form($form, &$form_state) {
  $form['ui_settings']['bg_image'] = array(
    '#title' => t('Background image'),
    '#type' => 'managed_file',
    '#description' => t('Please upload an image!'),
    '#progress_indicator' => 'bar',
    '#upload_location' => 'public://bg_images/',
  );

  $form['ui_settings']['bg_repeat'] = array(
    '#type' => 'checkbox',
    '#title' => t('Background repeat'),
    '#default_value' => 1,
  );
  $form['ui_settings']['bg_repeat_x'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat X'),
    '#default_value' => 1,
    '#states' => array(
      'visible' => array(
        ':input[name="bg_repeat"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['ui_settings']['bg_repeat_y'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat Y'),
    '#default_value' => 1,
    '#states' => array(
      'visible' => array(
        ':input[name="bg_repeat"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['ui_settings']['bg_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Color'),
    '#suffix' => '<div id="color-picker"></div>',
    '#default_value' => variable_get('ui_settings_bg_color', '#FFFFFF'),
    '#maxlength' => 7,
    '#size' => 7,
    '#attached' => array(
      'library' => array(
        array('system', 'farbtastic'),
      ),
      'js' => array(
        array(
          'type' => 'inline',
          'data' =>
            '(function($) {
              $(document).ready(function() {
                $("#color-picker").farbtastic("#edit-bg-color");
              });
            }) (jQuery);'
        ),
      )
    )
  );
  $form['ui_settings']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['ui_settings']['default'] = array(
    '#type' => 'submit',
    '#value' => t('Default value'),
  );
  return $form;
}

/**
 * Form submit callback
 */
function ui_elements_bg_form_submit($form, &$form_state) {
  if (!empty($form_state['values']['bg_image'])) {
    $file_obj = file_load($form_state['values']['bg_image']);
    if ($file_obj) {
      $file_obj->status = FILE_STATUS_PERMANENT;
      file_save($file_obj);
    }
    $bg_image = $form_state['values']['bg_image'];
  }
  else {
    $bg_image = 0;
  }
  $repeat = $form_state['values']['bg_repeat'];
  $repeat_x = $form_state['values']['bg_repeat_x'];
  $repeat_y = $form_state['values']['bg_repeat_y'];
  if (empty($repeat)) {
    $repeat = 'no-repeat';
  }
  else {
    if ((!empty($repeat_x) && !empty($repeat_y)) || (empty($repeat_x) && empty($repeat_y))) {
      $repeat = 'repeat';
    }
    elseif (!empty($repeat_x)) {
      $repeat = 'repeat-x';
    }
    elseif (!empty($repeat_y)) {
      $repeat = 'repeat-y';
    }
  }
  if ($form_state['values']['op'] == 'Default value') {
    $repeat = 'auto';
  }
  variable_set('ui_settings_bg_image_fid', $bg_image);
  variable_set('ui_settings_bg_repeat', $repeat);
  variable_set('ui_settings_bg_color', $form_state['values']['bg_color']);
}

/**
 * Form constructor for the form submit style settings.
 *
 * @see ui_elements_button_form_submit()
 * @ingroup forms
 */
function ui_elements_button_form($form, &$form_state) {
  if (_theme_exists("cb_old")) {
    $image = 'preview_old.png';
  }
  else {
    $image = 'buttons.png';
  }
  $active = array(
    'default' => t('Default'),
    '263248' => t('Gray'),
    '2CC36B' => t('Green'),
    '4AA3DF' => t('Blue'),
    'F16E3F' => t('Orange'),
    'EA6153' => t('Red'),
    'other' => t('Other'),
    'none' => t('None')
  );
  $form['ui_settings']['preview-image'] = array(
    '#type' => 'item',
    '#title' => t('Preview'),
    '#markup' => theme('image', array('path' => drupal_get_path('module', 'ui_elements') . "/images/$image")),
  );
  $form['ui_settings']['form_button'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('form-button-settings'),
    ),
  );
  $form['ui_settings']['form_button']['bg_default'] = array(
    '#type' => 'radios',
    '#title' => t('Default Buttons'),
    '#options' => $active,
  );
  $form['ui_settings']['form_button']['bg_rounded'] = array(
    '#type' => 'radios',
    '#title' => t('Rounded Buttons'),
    '#options' => $active,
  );
  $form['ui_settings']['form_button']['bg_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Color'),
    '#suffix' => '<div id="color-picker"></div>',
    '#default_value' => variable_get('ui_settings_button_color', '#FFFFFF'),
    '#maxlength' => 7,
    '#size' => 7,
    '#attached' => array(
      'library' => array(
        array('system', 'farbtastic'),
      ),
      'js' => array(
        array(
          'type' => 'inline',
          'data' =>
            '(function($) {
              $(document).ready(function() {
                $("#color-picker").farbtastic("#edit-bg-color");
              });
            }) (jQuery);'
        ),
      )
    )
  );
  $form['ui_settings']['pager_style'] = array(
    '#type' => 'radios',
    '#title' => t('Pager color'),
    '#options' => $active,
  );
  $form['ui_settings']['default_pager_style'] = array(
    '#type' => 'hidden',
    '#default_value' => variable_get('ui_settings_pager_style'),
  );
  $form['ui_settings']['pager_other_style'] = array(
    '#type' => 'textfield',
    '#title' => t('Color'),
    '#suffix' => '<div id="color-picker-pager"></div>',
    '#default_value' => variable_get('ui_settings_pager_style'),
    '#maxlength' => 7,
    '#size' => 7,
    '#attached' => array(
      'library' => array(
        array('system', 'farbtastic'),
      ),
      'js' => array(
        array(
          'type' => 'inline',
          'data' =>
            '(function($) {
              $(document).ready(function() {
                $("#color-picker-pager").farbtastic("#edit-pager-other-style");
              });
            }) (jQuery);'
        ),
      )
    )
  );
  $form['ui_settings']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Form submission handler for ui_elements_button_form().
 */
function ui_elements_button_form_submit($form, &$form_state) {
  $pager_style = $form_state['values']['pager_style'];
  $bg_rounded = $form_state['values']['bg_rounded'];
  $bg_default = $form_state['values']['bg_default'];

  $bg_color = 'none';
  if (!empty($bg_default) && $bg_default != 'none') {
    $bg_color = $bg_default;
    variable_set('ui_settings_button_rounded', 0);
  }
  elseif (!empty($bg_rounded) && $bg_rounded != 'none') {
    $bg_color = $bg_rounded;
    variable_set('ui_settings_button_rounded', 7);
  }
  switch ($bg_color) {
    case 'none':
      $color = $form_state['values']['bg_color'];
      break;

    case 'other':
      $color = $form_state['values']['bg_color'];
      break;

    case 'default':
      $color = '#0f7ad5';
      break;

    default:
      $color = '#' . $bg_color;
      break;
  }
  switch ($pager_style) {
    case 'other':
      $pager_style = $form_state['values']['pager_other_style'];
      break;

    case 'default':
      $pager_style = 'none';
      break;
    case '':
      $pager_style = variable_get('ui_settings_pager_style');
      break;

    default:
      $pager_style = '#' . $pager_style;
      break;
  }
  variable_set('ui_settings_pager_style', $pager_style);
  variable_set('ui_settings_button_color', $color);
}

/**
 * Form constructor for the page elements style settings.
 *
 * @see ui_elements_page_style_form_submit()
 * @ingroup forms
 */
function ui_elements_page_style_form($form, &$form_state) {
  if (_theme_exists("cb_old")) {
    $image = 'page_style.png';
  }
  else {
    $image = 'test_template.png';
  }
  $active = array(
    'default' => t('Default'),
    '263248' => t('Gray'),
    '2CC36B' => t('Green'),
    '4AA3DF' => t('Blue'),
    'F16E3F' => t('Orange'),
    'EA6153' => t('Red'),
    'other' => t('Other')
  );
  $form['ui_settings']['preview-image'] = array(
    '#type' => 'item',
    '#title' => t('Preview'),
    '#markup' => theme('image', array('path' => drupal_get_path('module', 'ui_elements') . "/images/$image")),
  );
  $form['ui_settings']['bg_default'] = array(
    '#type' => 'radios',
    '#title' => t('Default Buttons'),
    '#options' => $active,
  );
  $form['ui_settings']['page_style_color'] = array(
    '#type' => 'textfield',
    '#title' => t('Color'),
    '#suffix' => '<div id="color-picker-page-style"></div>',
    '#default_value' => variable_get('ui_settings_page_style_color'),
    '#maxlength' => 7,
    '#size' => 7,
    '#attached' => array(
      'library' => array(
        array('system', 'farbtastic'),
      ),
      'js' => array(
        array(
          'type' => 'inline',
          'data' =>
            '(function($) {
              $(document).ready(function() {
                $("#color-picker-page-style").farbtastic("#edit-page-style-color");
                // $("#color-picker-page-style").farbtastic("#edit-preview img");
              });
            }) (jQuery);'
        ),
      ),
    ),
  );
  $form['ui_settings']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Form submission handler for ui_elements_page_style_form().
 */
function ui_elements_page_style_form_submit($form, &$form_state) {
  if ($form_state['values']['bg_default'] == 'other') {
    $style_color = $form_state['values']['page_style_color'];
  }
  else {
    $style_color = '#' . $form_state['values']['bg_default'];
    if ($form_state['values']['bg_default'] == 'default') {
      $style_color = '#67B4E6';
    }
  }
  variable_set('ui_settings_page_style_color', $style_color);
}

function _theme_exists($theme_name) {
  $themes = list_themes();
  return isset($themes[$theme_name]) && $themes[$theme_name]->status == 1;
}
