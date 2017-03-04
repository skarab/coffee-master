function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6477\" class=\"headerLeftMenuInActive\"><a id=\"aID6477\" href=\"#\" OnMouseOver=\"link('_dir','config0',this)\" class=\"leftMenuLinkHeadInActive\">config</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1074\" class=\"leftMenuInActive\"><a id=\"aID1074\" href=\"#\" OnMouseOver=\"link('_class','Config38803',this)\" class=\"leftMenuLinkInActive\">Config</a></div>\n");
document.write("<div id=\"divID6197\" class=\"leftMenuInActive\"><a id=\"aID6197\" href=\"#\" OnMouseOver=\"link('_class','Object0',this)\" class=\"leftMenuLinkInActive\">Object</a></div>\n");
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
