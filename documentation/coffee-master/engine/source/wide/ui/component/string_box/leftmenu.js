function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6431\" class=\"headerLeftMenuInActive\"><a id=\"aID6431\" href=\"#\" OnMouseOver=\"link('_dir','string_box0',this)\" class=\"leftMenuLinkHeadInActive\">string_box</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID964\" class=\"leftMenuInActive\"><a id=\"aID964\" href=\"#\" OnMouseOver=\"link('_class','StringBox49249',this)\" class=\"leftMenuLinkInActive\">StringBox</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Functions</div>\n");
document.write("<div id=\"divID4618\" class=\"leftMenuInActive\"><a id=\"aID4618\" href=\"#\" OnMouseOver=\"link('_member','DoStringBox2514553380',this)\" class=\"leftMenuLinkInActive\">DoStringBox</a></div>\n");
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
