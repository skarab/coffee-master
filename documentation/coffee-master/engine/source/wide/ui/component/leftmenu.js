function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6507\" class=\"headerLeftMenuInActive\"><a id=\"aID6507\" href=\"#\" OnMouseOver=\"link('_dir','component0',this)\" class=\"leftMenuLinkHeadInActive\">component</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6427\" class=\"leftMenuInActive\"><a id=\"aID6427\" href=\"#\" OnMouseOver=\"link('_dir','file_dialog/file_dialog0',this)\" class=\"leftMenuLinkInActive\">file_dialog</a></div>\n");
document.write("<div id=\"divID6428\" class=\"leftMenuInActive\"><a id=\"aID6428\" href=\"#\" OnMouseOver=\"link('_dir','message_box/message_box0',this)\" class=\"leftMenuLinkInActive\">message_box</a></div>\n");
document.write("<div id=\"divID6429\" class=\"leftMenuInActive\"><a id=\"aID6429\" href=\"#\" OnMouseOver=\"link('_dir','property_window/property_window0',this)\" class=\"leftMenuLinkInActive\">property_window</a></div>\n");
document.write("<div id=\"divID6430\" class=\"leftMenuInActive\"><a id=\"aID6430\" href=\"#\" OnMouseOver=\"link('_dir','rename_box/rename_box0',this)\" class=\"leftMenuLinkInActive\">rename_box</a></div>\n");
document.write("<div id=\"divID6431\" class=\"leftMenuInActive\"><a id=\"aID6431\" href=\"#\" OnMouseOver=\"link('_dir','string_box/string_box0',this)\" class=\"leftMenuLinkInActive\">string_box</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
