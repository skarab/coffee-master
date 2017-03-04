function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6372\" class=\"headerLeftMenuInActive\"><a id=\"aID6372\" href=\"#\" OnMouseOver=\"link('_dir','gatherer0',this)\" class=\"leftMenuLinkHeadInActive\">gatherer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID877\" class=\"leftMenuInActive\"><a id=\"aID877\" href=\"#\" OnMouseOver=\"link('_class','Chunk54809',this)\" class=\"leftMenuLinkInActive\">Chunk</a></div>\n");
document.write("<div id=\"divID878\" class=\"leftMenuInActive\"><a id=\"aID878\" href=\"#\" OnMouseOver=\"link('_class','Gatherer54809',this)\" class=\"leftMenuLinkInActive\">Gatherer</a></div>\n");
document.write("<div id=\"divID879\" class=\"leftMenuInActive\"><a id=\"aID879\" href=\"#\" OnMouseOver=\"link('_class','Light54809',this)\" class=\"leftMenuLinkInActive\">Light</a></div>\n");
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
