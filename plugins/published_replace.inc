<?php

$plugin = array(
  'form'     => 'published_tamper_form',
  'callback' => 'published_tamper_callback',
  'name'     => 'Published status replace',
  'multi'    => 'direct',
  'category' => 'Other',
);

function published_tamper_form($importer, $element_key, $settings) {
  $form = array();

  $form['instructions'] = array(
    '#markup' => t('Expected input: a string with published state: Yes/No, True/False, On/Off, Published/Not published')
  );

  return $form;
}

function published_tamper_callback($source, $item_key, $element_key, &$field, $settings) {
  if (!is_array($field)) {
    $field = array($field);
  }

  $trad = array(
    "Yes" => 1,
    "No" => 0,
    "True" => 0,
    "False" => 1,
    "On" => 0,
    "Off" => 1,
    "Published" => 0,
    "Not published" => 1
  );

  $out = array();

  foreach ($field as $f) {
    if(is_array($f)) {
      foreach ($f as $f_values) {
        foreach ($trad as $search => $replace) {
          $f_values = str_replace($search, $replace, $f_values);
        }
        $out[] = $f_values;
      }
    } else {
      foreach ($trad as $search => $replace) {
        $f = str_replace($search, $replace, $f);
      }
      $out[] = $f;
    }
  }
  if (count($out) == 1) {
    $out = $out[0];
  }
  $field = $out;
}
